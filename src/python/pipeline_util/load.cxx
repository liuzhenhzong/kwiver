/*ckwg +5
 * Copyright 2011 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#include <python/helpers/pystream.h>
#include <python/helpers/python_convert_optional.h>

#include <vistk/pipeline_util/load_pipe.h>
#include <vistk/pipeline_util/load_pipe_exception.h>
#include <vistk/pipeline_util/pipe_declaration_types.h>

#include <vistk/pipeline/process.h>

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include <string>

/**
 * \file load.cxx
 *
 * \brief Python bindings for loading pipe blocks.
 */

using namespace boost::python;

static object pipe_block_config(vistk::pipe_block const& block);
static void pipe_block_config_set(vistk::pipe_block& block, vistk::config_pipe_block const& config);
static object pipe_block_process(vistk::pipe_block const& block);
static void pipe_block_process_set(vistk::pipe_block& block, vistk::process_pipe_block const& process);
static object pipe_block_connect(vistk::pipe_block const& block);
static void pipe_block_connect_set(vistk::pipe_block& block, vistk::connect_pipe_block const& connect);
static object pipe_block_group(vistk::pipe_block const& block);
static void pipe_block_group_set(vistk::pipe_block& block, vistk::group_pipe_block const& group);
static vistk::pipe_blocks load_pipe_file(std::string const& path);
static vistk::pipe_blocks load_pipe(object const& stream, std::string const& inc_root);

static void translator(vistk::load_pipe_exception const& e);

class block_visitor
  : public boost::static_visitor<object>
{
  public:
    typedef enum
    {
      BLOCK_CONFIG,
      BLOCK_PROCESS,
      BLOCK_CONNECT,
      BLOCK_GROUP
    } block_t;

    block_visitor(block_t type);
    ~block_visitor();

    block_t const block_type;

    object operator () (vistk::config_pipe_block const& config_block) const;
    object operator () (vistk::process_pipe_block const& process_block) const;
    object operator () (vistk::connect_pipe_block const& connect_block) const;
    object operator () (vistk::group_pipe_block const& group_block) const;
};

BOOST_PYTHON_MODULE(load)
{
  register_exception_translator<
    vistk::load_pipe_exception>(translator);

  REGISTER_OPTIONAL_CONVERTER(vistk::config_flags_t);
  REGISTER_OPTIONAL_CONVERTER(vistk::config_provider_t);
  REGISTER_OPTIONAL_CONVERTER(vistk::process::port_flags_t);

  class_<vistk::token_t>("Token"
    , "A token in the pipeline description.");
  class_<vistk::config_flag_t>("ConfigFlag"
    , "A flag on a configuration setting.");
  class_<vistk::config_flags_t>("ConfigFlags"
    , "A collection of flags on a configuration setting.")
    .def(vector_indexing_suite<vistk::config_flags_t>())
  ;
  class_<vistk::config_provider_t>("ConfigProvider"
    , "A provider key for a configuration setting.");
  class_<vistk::config_key_options_t>("ConfigKeyOptions"
    , "A collection of options on a configuration setting.")
    .def_readwrite("flags", &vistk::config_key_options_t::flags)
    .def_readwrite("provider", &vistk::config_key_options_t::provider)
  ;
  class_<vistk::config_key_t>("ConfigKey"
    , "A configuration key with its settings.")
    .def_readwrite("key_path", &vistk::config_key_t::key_path)
    .def_readwrite("options", &vistk::config_key_t::options)
  ;
  class_<vistk::config_value_t>("ConfigValue"
    , "A complete configuration setting.")
    .def_readwrite("key", &vistk::config_value_t::key)
    .def_readwrite("value", &vistk::config_value_t::value)
  ;
  class_<vistk::config_values_t>("ConfigValues"
    , "A collection of configuration settings.")
    /// \todo Need operator == on config_value_t
    //.def(vector_indexing_suite<vistk::config_values_t>())
  ;
  class_<vistk::map_options_t>("MapOptions"
    , "A collection of options for a mapping.")
    .def_readwrite("flags", &vistk::map_options_t::flags)
  ;
  class_<vistk::input_map_t>("InputMap"
    , "An input mapping for a group.")
    .def_readwrite("options", &vistk::input_map_t::options)
    .def_readwrite("from_", &vistk::input_map_t::from)
    .def_readwrite("to", &vistk::input_map_t::to)
  ;
  class_<vistk::input_maps_t>("InputMaps"
    , "A collection of input mappings.")
    /// \todo Need operator == on input_map_t.
    //.def(vector_indexing_suite<vistk::input_maps_t>())
  ;
  class_<vistk::output_map_t>("OutputMap"
    , "An output mapping for a group.")
    .def_readwrite("options", &vistk::output_map_t::options)
    .def_readwrite("from_", &vistk::output_map_t::from)
    .def_readwrite("to", &vistk::output_map_t::to)
  ;
  class_<vistk::output_maps_t>("OutputMaps"
    , "A collection of output mappings.")
    /// \todo Need operator == on output_map_t.
    //.def(vector_indexing_suite<vistk::output_maps_t>())
  ;
  class_<vistk::config_pipe_block>("ConfigBlock"
    , "A block of configuration settings.")
    .def_readwrite("key", &vistk::config_pipe_block::key)
    .def_readwrite("values", &vistk::config_pipe_block::values)
  ;
  class_<vistk::process_pipe_block>("ProcessBlock"
    , "A block which declares a process.")
    .def_readwrite("name", &vistk::process_pipe_block::name)
    .def_readwrite("type", &vistk::process_pipe_block::type)
    .def_readwrite("config_values", &vistk::process_pipe_block::config_values)
  ;
  class_<vistk::connect_pipe_block>("ConnectBlock"
    , "A block which connects two ports together.")
    .def_readwrite("from_", &vistk::connect_pipe_block::from)
    .def_readwrite("to", &vistk::connect_pipe_block::to)
  ;
  class_<vistk::group_pipe_block>("GroupBlock"
    , "A block which declares a group within the pipeline.")
    .def_readwrite("name", &vistk::group_pipe_block::name)
    .def_readwrite("config_values", &vistk::group_pipe_block::config_values)
    .def_readwrite("input_mappings", &vistk::group_pipe_block::input_mappings)
    .def_readwrite("output_mappings", &vistk::group_pipe_block::output_mappings)
  ;
  class_<vistk::pipe_block>("PipeBlock"
    , "A block in a pipeline declaration file.")
    .add_property("config", &pipe_block_config, &pipe_block_config_set)
    .add_property("process", &pipe_block_process, &pipe_block_process_set)
    .add_property("connect", &pipe_block_connect, &pipe_block_connect_set)
    .add_property("group", &pipe_block_group, &pipe_block_group_set)
  ;
  class_<vistk::pipe_blocks>("PipeBlocks"
    , "A collection of pipeline blocks.")
    /// \todo Need operator == on pipe_block.
    //.def(vector_indexing_suite<vistk::pipe_blocks>())
  ;

  def("load_pipe_file", &load_pipe_file
    , (arg("path"))
    , "Load pipe blocks from a file.");
  def("load_pipe", &load_pipe
    , (arg("stream"), arg("inc_root") = std::string())
    , "Load pipe blocks from a stream.");
}

void
translator(vistk::load_pipe_exception const& e)
{
  PyErr_SetString(PyExc_RuntimeError, e.what());
}

object
pipe_block_config(vistk::pipe_block const& block)
{
  return boost::apply_visitor(block_visitor(block_visitor::BLOCK_CONFIG), block);
}

void
pipe_block_config_set(vistk::pipe_block& block, vistk::config_pipe_block const& config)
{
  block = config;
}

object
pipe_block_process(vistk::pipe_block const& block)
{
  return boost::apply_visitor(block_visitor(block_visitor::BLOCK_PROCESS), block);
}

void
pipe_block_process_set(vistk::pipe_block& block, vistk::process_pipe_block const& process)
{
  block = process;
}

object
pipe_block_connect(vistk::pipe_block const& block)
{
  return boost::apply_visitor(block_visitor(block_visitor::BLOCK_CONNECT), block);
}

void
pipe_block_connect_set(vistk::pipe_block& block, vistk::connect_pipe_block const& connect)
{
  block = connect;
}

object
pipe_block_group(vistk::pipe_block const& block)
{
  return boost::apply_visitor(block_visitor(block_visitor::BLOCK_GROUP), block);
}

void
pipe_block_group_set(vistk::pipe_block& block, vistk::group_pipe_block const& group)
{
  block = group;
}

vistk::pipe_blocks
load_pipe_file(std::string const& path)
{
  return vistk::load_pipe_blocks_from_file(boost::filesystem::path(path));
}

vistk::pipe_blocks
load_pipe(object const& stream, std::string const& inc_root)
{
  pyistream istr(stream);

  return vistk::load_pipe_blocks(istr, boost::filesystem::path(inc_root));
}

block_visitor
::block_visitor(block_t type)
  : block_type(type)
{
}

block_visitor
::~block_visitor()
{
}

object
block_visitor
::operator () (vistk::config_pipe_block const& config_block) const
{
  if (block_type == BLOCK_CONFIG)
  {
    return object(config_block);
  }

  return object();
}

object
block_visitor
::operator () (vistk::process_pipe_block const& process_block) const
{
  if (block_type == BLOCK_PROCESS)
  {
    return object(process_block);
  }

  return object();
}

object
block_visitor
::operator () (vistk::connect_pipe_block const& connect_block) const
{
  if (block_type == BLOCK_CONNECT)
  {
    return object(connect_block);
  }

  return object();
}

object
block_visitor
::operator () (vistk::group_pipe_block const& group_block) const
{
  if (block_type == BLOCK_GROUP)
  {
    return object(group_block);
  }

  return object();
}

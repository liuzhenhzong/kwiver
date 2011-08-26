/*ckwg +5
 * Copyright 2011 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#ifndef VISTK_PIPELINE_UTIL_PIPE_BAKERY_EXCEPTION_H
#define VISTK_PIPELINE_UTIL_PIPE_BAKERY_EXCEPTION_H

#include "pipeline_util-config.h"

#include "pipe_declaration_types.h"

/**
 * \file pipe_bakery_exception.h
 *
 * \brief Header for exceptions used when baking a pipeline.
 */

namespace vistk
{

/**
 * \class pipe_bakery_exception pipe_bakery_exception.h <vistk/pipeline_util/pipe_bakery_exception.h>
 *
 * \brief The base class for all exceptions thrown when baking a pipeline.
 *
 * \ingroup exceptions
 */
class VISTK_PIPELINE_UTIL_EXPORT pipe_bakery_exception
  : public pipeline_exception
{
};

/**
 * \class unrecognized_config_flag_exception pipe_bakery_exception.h <vistk/pipeline_util/pipe_bakery_exception.h>
 *
 * \brief The exception thrown when a flag on a configuration is not recognized.
 *
 * \ingroup exceptions
 */
class VISTK_PIPELINE_UTIL_EXPORT unrecognized_config_flag_exception
  : public pipe_bakery_exception
{
  public:
    /**
     * \brief Constructor.
     *
     * \param key The key the flag was on.
     * \param flag The unrecognized flag.
     */
    unrecognized_config_flag_exception(config::key_t const& key, config_flag_t const& flag) throw();
    /**
     * \brief Destructor.
     */
    ~unrecognized_config_flag_exception() throw();

    /// The key the flag was on.
    config::key_t const m_key;
    /// The unrecognized flag.
    config_flag_t const m_flag;
};

/**
 * \class unrecognized_provider_exception pipe_bakery_exception.h <vistk/pipeline_util/pipe_bakery_exception.h>
 *
 * \brief The exception thrown when a configuration provider request key is unknown.
 *
 * \ingroup exceptions
 */
class VISTK_PIPELINE_UTIL_EXPORT unrecognized_provider_exception
  : public pipe_bakery_exception
{
  public:
    /**
     * \brief Constructor.
     *
     * \param key The key the flag was on.
     * \param provider The unrecognized provider.
     * \param index The index requested from the provider.
     */
    unrecognized_provider_exception(config::key_t const& key, config_provider_t const& provider, config::value_t const& index) throw();
    /**
     * \brief Destructor.
     */
    ~unrecognized_provider_exception() throw();

    /// The key the flag was on.
    config::key_t const m_key;
    /// The unrecognized provider.
    config_provider_t const m_provider;
    /// The index requested from the provider.
    config::value_t const m_index;
};

/**
 * \class circular_config_provide_exception pipe_bakery_exception.h <vistk/pipeline_util/pipe_bakery_exception.h>
 *
 * \brief The exception thrown when configuration provider requests are circular.
 *
 * \ingroup exceptions
 */
class VISTK_PIPELINE_UTIL_EXPORT circular_config_provide_exception
  : public pipe_bakery_exception
{
  public:
    /**
     * \brief Constructor.
     */
    circular_config_provide_exception() throw();
    /**
     * \brief Destructor.
     */
    ~circular_config_provide_exception() throw();
};

/**
 * \class unrecognized_system_index_exception pipe_bakery_exception.h <vistk/pipeline_util/pipe_bakery_exception.h>
 *
 * \brief The exception thrown when the system provider does not know about an index.
 *
 * \ingroup exceptions
 */
class VISTK_PIPELINE_UTIL_EXPORT unrecognized_system_index_exception
  : public pipe_bakery_exception
{
  public:
    /**
     * \brief Constructor.
     */
    unrecognized_system_index_exception(config::value_t const& index) throw();
    /**
     * \brief Destructor.
     */
    ~unrecognized_system_index_exception() throw();

    /// The index that was requested.
    config::value_t const m_index;
};

}

#endif // VISTK_PIPELINE_UTIL_PIPE_BAKERY_EXCEPTION_H

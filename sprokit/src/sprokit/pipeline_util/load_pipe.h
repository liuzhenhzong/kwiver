/*ckwg +29
 * Copyright 2011-2013 by Kitware, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither name of Kitware, Inc. nor the names of any contributors may be used
 *    to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SPROKIT_PIPELINE_UTIL_LOAD_PIPE_H
#define SPROKIT_PIPELINE_UTIL_LOAD_PIPE_H

#include "pipeline_util-config.h"

#include "path.h"
#include "pipe_declaration_types.h"

#include <iosfwd>

/**
 * \file load_pipe.h
 *
 * \brief Load a pipeline declaration from a stream.
 */

namespace sprokit
{

/**
 * \brief Convert a pipeline description file into a collection of pipeline blocks.
 *
 * \param fname The file to load the pipeline blocks from.
 *
 * \returns A new set of pipeline blocks.
 */
SPROKIT_PIPELINE_UTIL_EXPORT pipe_blocks load_pipe_blocks_from_file(path_t const& fname);

/**
 * \brief Convert a pipeline description into a pipeline.
 *
 * \param istr The stream to load the pipeline from.
 * \param inc_root The root directory to search for includes from.
 *
 * \returns A new set of pipeline blocks.
 */
SPROKIT_PIPELINE_UTIL_EXPORT pipe_blocks load_pipe_blocks(std::istream& istr, path_t const& inc_root = "");

/**
 * \brief Convert a cluster description file into a collection of cluster blocks.
 *
 * \param fname The file to load the cluster blocks from.
 *
 * \returns A new set of cluster blocks.
 */
cluster_blocks SPROKIT_PIPELINE_UTIL_EXPORT load_cluster_blocks_from_file(path_t const& fname);

/**
 * \brief Convert a cluster description into a cluster.
 *
 * \param istr The stream to load the cluster from.
 * \param inc_root The root directory to search for includes from.
 *
 * \returns A new set of cluster blocks.
 */
cluster_blocks SPROKIT_PIPELINE_UTIL_EXPORT load_cluster_blocks(std::istream& istr, path_t const& inc_root = "");

}

#endif // SPROKIT_PIPELINE_UTIL_LOAD_PIPE_H
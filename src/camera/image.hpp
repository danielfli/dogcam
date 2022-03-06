/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2021, Raspberry Pi (Trading) Ltd.
 *
 * image.hpp - still image encoder declarations
 */

#pragma once

#include <string>

#include <libcamera/base/span.h>

#include <libcamera/controls.h>

#include "stream_info.hpp"

struct StillOptions;

// In jpeg.cpp:
void jpeg_save(std::vector<libcamera::Span<uint8_t>> const &mem, StreamInfo const &info,
			   libcamera::ControlList const &metadata, std::string const &filename, std::string const &cam_name
			   );
//StillOptions const *options
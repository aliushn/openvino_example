// Copyright (c) 2018 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @brief A header file that provides macros to handle no exception methods
 * @file ie_exception_conversion.hpp
 */
#pragma once
#include <ie_common.h>

#define CALL_STATUS_FNC(function, ...)\
ResponseDesc resp;\
auto res = actual->function(__VA_ARGS__, &resp);\
if (res != OK) InferenceEngine::details::extract_exception(res, resp.msg);

#define CALL_STATUS_FNC_NO_ARGS(function)\
ResponseDesc resp;\
auto res = actual->function(&resp);\
if (res != OK) InferenceEngine::details::extract_exception(res, resp.msg);


#define CALL_FNC(function, ...)\
ResponseDesc resp;\
auto result = actual->function(__VA_ARGS__, &resp);\
if (resp.msg[0] != '\0') {\
    THROW_IE_EXCEPTION << resp.msg;\
}\
return result;

#define CALL_FNC_REF(function, ...)\
ResponseDesc resp;\
auto & result = actual->function(__VA_ARGS__, &resp);\
if (resp.msg[0] != '\0') {\
    THROW_IE_EXCEPTION << resp.msg;\
}\
return result;

#define CALL_FNC_NO_ARGS(function)\
ResponseDesc resp;\
auto result = actual->function(&resp);\
if (resp.msg[0] != '\0') {\
    THROW_IE_EXCEPTION << resp.msg;\
}\
return result;

#define CALL_FNC_NO_ARGS_REF(function)\
ResponseDesc resp;\
auto & result = actual->function(&resp);\
if (resp.msg[0] != '\0') {\
    THROW_IE_EXCEPTION << resp.msg;\
}\
return result;

namespace InferenceEngine {
namespace details {

inline void extract_exception(StatusCode status, char *msg) {
    switch (status) {
        case NOT_IMPLEMENTED:throw NotImplemented(msg);
        case NETWORK_NOT_LOADED:throw NetworkNotLoaded(msg);
        case PARAMETER_MISMATCH:throw ParameterMismatch(msg);
        case NOT_FOUND:throw NotFound(msg);
        case OUT_OF_BOUNDS:throw OutOfBounds(msg);
        case UNEXPECTED:throw Unexpected(msg);
        case REQUEST_BUSY:throw RequestBusy(msg);
        case RESULT_NOT_READY:throw ResultNotReady(msg);
        case NOT_ALLOCATED:throw NotAllocated(msg);
        case INFER_NOT_STARTED:throw InferNotStarted(msg);
        default:THROW_IE_EXCEPTION << msg;
    }
}

}  // namespace details
}  // namespace InferenceEngine
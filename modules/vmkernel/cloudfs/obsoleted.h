/*
Copyright (c) 2007-2011 VMware, Inc. All Rights Reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted (subject to the limitations in the
disclaimer below) provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the
   distribution.

* Neither the name of VMware nor the names of its
   contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
GRANTED BY THIS LICENSE.  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __OBSOLETED_H__
#define __OBSOLETED_H__

#include "logfsConstants.h"
#include "logtypes.h"
#include "binHeap.h"

#define LOGFS_OBS_MAX_REMAPS 64

typedef struct {
   SP_SpinLock lock;
   LogFS_BinHeap heap;
   int numCandidateSegments;

   struct {
      log_segment_id_t from, to;
   } remaps[LOGFS_OBS_MAX_REMAPS];
   int numRemaps;

} LogFS_ObsoletedSegments;

struct LogFS_MetaLog;

void LogFS_ObsoletedSegmentsInit(LogFS_ObsoletedSegments *os);
void LogFS_ObsoletedSegmentsCleanup(LogFS_ObsoletedSegments *os);
void LogFS_ObsoletedSegmentsAdd(LogFS_ObsoletedSegments *os,
                                log_segment_id_t segment, int howmany);
int LogFS_ObsoletedSegmentsGetCandidates(LogFS_ObsoletedSegments *os,
                                         struct LogFS_MetaLog *ml,
                                         void **candidates, int max_candidates);
void LogFS_ObsoletedSegmentsRemapSegment(LogFS_ObsoletedSegments *os,
                                         log_segment_id_t from,
                                         log_segment_id_t to);
void LogFS_ObsoletedSegmentsClearRemaps(LogFS_ObsoletedSegments *os);
#endif

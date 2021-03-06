//
//  ConflictTest.h
//  CouchbaseLite
//
//  Copyright (c) 2017 Couchbase, Inc All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#import "CBLTestCase.h"

NS_ASSUME_NONNULL_BEGIN

@interface TestResolver : NSObject <CBLConflictResolver>
@property (atomic) BOOL requireBaseRevision;
@property (readonly, atomic) BOOL wasCalled;
@end

/** Default Conflict Resolution set to ConflictTest which 
    will just make the assertion false as shouldn't be called. */
@interface DoNotResolve : TestResolver
@end

/** Select my version. */
@interface MineWins : TestResolver
@end

/** Select their version. */
@interface TheirsWins : TestResolver
@end

/** Merge, but if both sides changed the same property then use their value. */
@interface MergeThenTheirsWins : TestResolver
@end

/** Return nil to give up the conflict resolving. The document save operation will return 
    the conflicting error. */
@interface GiveUp : TestResolver
@end

/** Block based resolver */
@interface BlockResolver : TestResolver

@property (atomic, readonly) CBLDocument* (^block)(CBLConflict*);

- (instancetype) initWithBlock: (nullable CBLDocument* (^)(CBLConflict*))block;

@end

NS_ASSUME_NONNULL_END

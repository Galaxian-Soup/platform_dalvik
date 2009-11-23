/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * This file contains register alloction support and is intended to be
 * included by:
 *
 *        Codegen-$(TARGET_ARCH_VARIANT).c
 *
 */

#include "compiler/CompilerIR.h"

/*
 * loadConstant() sometimes needs to add a small imm to a pre-existing constant
 */
static ArmLIR *opRegImm(CompilationUnit *cUnit, OpKind op, int rDestSrc1,
                        int value);
static ArmLIR *opRegReg(CompilationUnit *cUnit, OpKind op, int rDestSrc1,
                        int rSrc2);

/* Forward decalraton the portable versions due to circular dependency */
static bool genArithOpFloatPortable(CompilationUnit *cUnit, MIR *mir,
                                    RegLocation rlDest, RegLocation rlSrc1,
                                    RegLocation rlSrc2);

static bool genArithOpDoublePortable(CompilationUnit *cUnit, MIR *mir,
                                     RegLocation rlDest, RegLocation rlSrc1,
                                     RegLocation rlSrc2);

static bool genConversionPortable(CompilationUnit *cUnit, MIR *mir);

static void genMonitorPortable(CompilationUnit *cUnit, MIR *mir);


/*
 * Architecture-dependent register allocation routines implemented in
 * Thumb[2]/Ralloc.c
 */
extern int dvmCompilerAllocTypedTempPair(CompilationUnit *cUnit,
                                         bool fpHint, int regClass);

extern int dvmCompilerAllocTypedTemp(CompilationUnit *cUnit, bool fpHint,
                                     int regClass);

extern ArmLIR* dvmCompilerRegCopyNoInsert(CompilationUnit *cUnit, int rDest,
                                          int rSrc);

extern ArmLIR* dvmCompilerRegCopy(CompilationUnit *cUnit, int rDest, int rSrc);

extern void dvmCompilerRegCopyWide(CompilationUnit *cUnit, int destLo,
                                   int destHi, int srcLo, int srcHi);

extern void dvmCompilerFlushRegImpl(CompilationUnit *cUnit, int rBase,
                                    int displacement, int rSrc, OpSize size);

extern void dvmCompilerFlushRegWideImpl(CompilationUnit *cUnit, int rBase,
                                        int displacement, int rSrcLo,
                                        int rSrcHi);

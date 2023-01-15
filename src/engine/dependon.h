﻿#if !defined(AFX_SK_H__80671DE0_DF45_4508_8EC6_DE5B285CC55E__HEAD__)
#define AFX_SK_H__80671DE0_DF45_4508_8EC6_DE5B285CC55E__HEAD__

#pragma warning(disable: 4996 4141 4146 4244 4267 4291 4351 4456 4457 4458 4459 4503 4624 4722 4100 4127 4512 4505 4610 4510 4702 4245 4706 4310 4701 4703 4389 4611 4805 4204 4577 4091 4592 4319 4709 4324)

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Driver/Options.h"
#include "clang/CodeGen/ModuleBuilder.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/CompilerInvocation.h"
#include "clang/FrontendTool/Utils.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/PreprocessorOptions.h"
#include "clang/Frontend/TextDiagnosticBuffer.h"
#include "clang/Parse/ParseAST.h"
#include "clang/Sema/Sema.h"
#include "clang/Frontend/Utils.h"
#include "clang/Basic/DiagnosticIDs.h"
#include "clang/Frontend/FrontendDiagnostic.h"
#include "llvm/ADT/Triple.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Bitcode/BitcodeReader.h"
#include "llvm/CodeGen/CommandFlags.h"
#include "llvm/CodeGen/LinkAllCodegenComponents.h"
#include "llvm/Config/llvm-config.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/ExecutionEngine/JITEventListener.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/ObjectCache.h"
#include "llvm/ExecutionEngine/Orc/DebugUtils.h"
#include "llvm/ExecutionEngine/Orc/ExecutionUtils.h"
#include "llvm/ExecutionEngine/Orc/JITTargetMachineBuilder.h"
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/MachOPlatform.h"
#include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
#include "llvm/ExecutionEngine/Orc/TargetProcess/TargetExecutionUtils.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/Object/Archive.h"
#include "llvm/Object/ObjectFile.h"
#include "llvm/Transforms/Instrumentation.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/TimeProfiler.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/Process.h"
#include "llvm/Support/Timer.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Support/Format.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/Memory.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/PluginLoader.h"
#include "llvm/Support/Program.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/WithColor.h"
#include "llvm/Support/raw_ostream.h"

#pragma comment(lib,"LLVMAArch64CodeGen.lib")
#pragma comment(lib,"LLVMAArch64AsmParser.lib")
#pragma comment(lib,"LLVMAArch64Desc.lib")
#pragma comment(lib,"LLVMAArch64Disassembler.lib")
#pragma comment(lib,"LLVMAArch64Info.lib")
#pragma comment(lib,"LLVMAArch64Utils.lib")
#pragma comment(lib,"LLVMAMDGPUCodeGen.lib")
#pragma comment(lib,"LLVMAMDGPUAsmParser.lib")
#pragma comment(lib,"LLVMAMDGPUDesc.lib")
#pragma comment(lib,"LLVMAMDGPUDisassembler.lib")
#pragma comment(lib,"LLVMAMDGPUInfo.lib")
#pragma comment(lib,"LLVMAMDGPUUtils.lib")
#pragma comment(lib,"LLVMARMCodeGen.lib")
#pragma comment(lib,"LLVMARMAsmParser.lib")
#pragma comment(lib,"LLVMARMDesc.lib")
#pragma comment(lib,"LLVMARMDisassembler.lib")
#pragma comment(lib,"LLVMARMInfo.lib")
#pragma comment(lib,"LLVMARMUtils.lib")
#pragma comment(lib,"LLVMAVRCodeGen.lib")
#pragma comment(lib,"LLVMAVRAsmParser.lib")
#pragma comment(lib,"LLVMAVRDesc.lib")
#pragma comment(lib,"LLVMAVRDisassembler.lib")
#pragma comment(lib,"LLVMAVRInfo.lib")
#pragma comment(lib,"LLVMBPFCodeGen.lib")
#pragma comment(lib,"LLVMBPFAsmParser.lib")
#pragma comment(lib,"LLVMBPFDesc.lib")
#pragma comment(lib,"LLVMBPFDisassembler.lib")
#pragma comment(lib,"LLVMBPFInfo.lib")
#pragma comment(lib,"LLVMHexagonCodeGen.lib")
#pragma comment(lib,"LLVMHexagonAsmParser.lib")
#pragma comment(lib,"LLVMHexagonDesc.lib")
#pragma comment(lib,"LLVMHexagonDisassembler.lib")
#pragma comment(lib,"LLVMHexagonInfo.lib")
#pragma comment(lib,"LLVMLanaiCodeGen.lib")
#pragma comment(lib,"LLVMLanaiAsmParser.lib")
#pragma comment(lib,"LLVMLanaiDesc.lib")
#pragma comment(lib,"LLVMLanaiDisassembler.lib")
#pragma comment(lib,"LLVMLanaiInfo.lib")
#pragma comment(lib,"LLVMMipsCodeGen.lib")
#pragma comment(lib,"LLVMMipsAsmParser.lib")
#pragma comment(lib,"LLVMMipsDesc.lib")
#pragma comment(lib,"LLVMMipsDisassembler.lib")
#pragma comment(lib,"LLVMMipsInfo.lib")
#pragma comment(lib,"LLVMMSP430CodeGen.lib")
#pragma comment(lib,"LLVMMSP430AsmParser.lib")
#pragma comment(lib,"LLVMMSP430Desc.lib")
#pragma comment(lib,"LLVMMSP430Disassembler.lib")
#pragma comment(lib,"LLVMMSP430Info.lib")
#pragma comment(lib,"LLVMNVPTXCodeGen.lib")
#pragma comment(lib,"LLVMNVPTXDesc.lib")
#pragma comment(lib,"LLVMNVPTXInfo.lib")
#pragma comment(lib,"LLVMPowerPCCodeGen.lib")
#pragma comment(lib,"LLVMPowerPCAsmParser.lib")
#pragma comment(lib,"LLVMPowerPCDesc.lib")
#pragma comment(lib,"LLVMPowerPCDisassembler.lib")
#pragma comment(lib,"LLVMPowerPCInfo.lib")
#pragma comment(lib,"LLVMRISCVCodeGen.lib")
#pragma comment(lib,"LLVMRISCVAsmParser.lib")
#pragma comment(lib,"LLVMRISCVDesc.lib")
#pragma comment(lib,"LLVMRISCVDisassembler.lib")
#pragma comment(lib,"LLVMRISCVInfo.lib")
#pragma comment(lib,"LLVMSparcCodeGen.lib")
#pragma comment(lib,"LLVMSparcAsmParser.lib")
#pragma comment(lib,"LLVMSparcDesc.lib")
#pragma comment(lib,"LLVMSparcDisassembler.lib")
#pragma comment(lib,"LLVMSparcInfo.lib")
#pragma comment(lib,"LLVMSystemZCodeGen.lib")
#pragma comment(lib,"LLVMSystemZAsmParser.lib")
#pragma comment(lib,"LLVMSystemZDesc.lib")
#pragma comment(lib,"LLVMSystemZDisassembler.lib")
#pragma comment(lib,"LLVMSystemZInfo.lib")
#pragma comment(lib,"LLVMWebAssemblyCodeGen.lib")
#pragma comment(lib,"LLVMWebAssemblyAsmParser.lib")
#pragma comment(lib,"LLVMWebAssemblyDesc.lib")
#pragma comment(lib,"LLVMWebAssemblyDisassembler.lib")
#pragma comment(lib,"LLVMWebAssemblyInfo.lib")
#pragma comment(lib,"LLVMWebAssemblyUtils.lib")
#pragma comment(lib,"LLVMX86CodeGen.lib")
#pragma comment(lib,"LLVMX86AsmParser.lib")
#pragma comment(lib,"LLVMX86Desc.lib")
#pragma comment(lib,"LLVMX86Disassembler.lib")
#pragma comment(lib,"LLVMX86Info.lib")
#pragma comment(lib,"LLVMXCoreCodeGen.lib")
#pragma comment(lib,"LLVMXCoreDesc.lib")
#pragma comment(lib,"LLVMXCoreDisassembler.lib")
#pragma comment(lib,"LLVMXCoreInfo.lib")
#pragma comment(lib,"LLVMAnalysis.lib")
#pragma comment(lib,"LLVMCodeGen.lib")
#pragma comment(lib,"LLVMCore.lib")
#pragma comment(lib,"LLVMipo.lib")
#pragma comment(lib,"LLVMAggressiveInstCombine.lib")
#pragma comment(lib,"LLVMInstCombine.lib")
#pragma comment(lib,"LLVMInstrumentation.lib")
#pragma comment(lib,"LLVMMC.lib")
#pragma comment(lib,"LLVMMCParser.lib")
#pragma comment(lib,"LLVMObjCARCOpts.lib")
#pragma comment(lib,"LLVMOption.lib")
#pragma comment(lib,"LLVMScalarOpts.lib")
#pragma comment(lib,"LLVMSupport.lib")
#pragma comment(lib,"LLVMTransformUtils.lib")
#pragma comment(lib,"LLVMVectorize.lib")
#pragma comment(lib,"LLVMMIRParser.lib")
#pragma comment(lib,"LLVMGlobalISel.lib")
#pragma comment(lib,"LLVMCFGuard.lib")
#pragma comment(lib,"LLVMAsmPrinter.lib")
#pragma comment(lib,"LLVMDebugInfoDWARF.lib")
#pragma comment(lib,"LLVMDebugInfoMSF.lib")
#pragma comment(lib,"LLVMSelectionDAG.lib")
#pragma comment(lib,"LLVMMCDisassembler.lib")
#pragma comment(lib,"LLVMCoverage.lib")
#pragma comment(lib,"LLVMLTO.lib")
#pragma comment(lib,"LLVMPasses.lib")
#pragma comment(lib,"LLVMTarget.lib")
#pragma comment(lib,"LLVMCoroutines.lib")
#pragma comment(lib,"LLVMIRReader.lib")
#pragma comment(lib,"LLVMAsmParser.lib")
#pragma comment(lib,"LLVMBitWriter.lib")
#pragma comment(lib,"LLVMLinker.lib")
#pragma comment(lib,"LLVMExtensions.lib")
#pragma comment(lib,"LLVMFrontendOpenMP.lib")
#pragma comment(lib,"LLVMProfileData.lib")
#pragma comment(lib,"LLVMObject.lib")
#pragma comment(lib,"LLVMDebugInfoCodeView.lib")
#pragma comment(lib,"LLVMBitReader.lib")
#pragma comment(lib,"LLVMTextAPI.lib")
#pragma comment(lib,"LLVMBinaryFormat.lib")
#pragma comment(lib,"LLVMRemarks.lib")
#pragma comment(lib,"LLVMBitstreamReader.lib")
#pragma comment(lib,"LLVMDemangle.lib")
#pragma comment(lib,"LLVMExecutionEngine.lib")
#pragma comment(lib,"LLVMInterpreter.lib")
#pragma comment(lib,"LLVMJITLink.lib")
#pragma comment(lib,"LLVMMCJIT.lib")
#pragma comment(lib,"LLVMOrcShared.lib")
#pragma comment(lib,"LLVMOrcJIT.lib")
#pragma comment(lib,"LLVMOrcTargetProcess.lib")
#pragma comment(lib,"LLVMRuntimeDyld.lib")
#pragma comment(lib,"LLVMVEInfo.lib")
#pragma comment(lib,"LLVMVEDesc.lib")
#pragma comment(lib,"LLVMVEDisassembler.lib")
#pragma comment(lib,"LLVMVEAsmParser.lib")
#pragma comment(lib,"LLVMVECodeGen.lib")
#pragma comment(lib,"LLVMLoongArchInfo.lib")
#pragma comment(lib,"LLVMLoongArchDesc.lib")
#pragma comment(lib,"LLVMLoongArchCodeGen.lib")
#pragma comment(lib,"LLVMTargetParser.lib")
#pragma comment(lib,"LLVMWindowsDriver.lib")
#pragma comment(lib,"LLVMIRPrinter.lib")
#pragma comment(lib,"LLVMFrontendHLSL.lib")
#pragma comment(lib,"LLVMLoongArchAsmParser.lib")

#pragma comment(lib,"clangFormat.lib")
#pragma comment(lib,"clangToolingInclusions.lib")
#pragma comment(lib,"clangToolingCore.lib")
#pragma comment(lib,"clangRewrite.lib")
#pragma comment(lib,"clangLex.lib")
#pragma comment(lib,"clangBasic.lib")
#pragma comment(lib,"clangCodeGen.lib")
#pragma comment(lib,"clangDriver.lib")
#pragma comment(lib,"clangFrontend.lib")
#pragma comment(lib,"clangFrontendTool.lib")
#pragma comment(lib,"clangSerialization.lib")
#pragma comment(lib,"clangRewriteFrontend.lib")
#pragma comment(lib,"clangARCMigrate.lib")
#pragma comment(lib,"clangStaticAnalyzerFrontend.lib")
#pragma comment(lib,"clangStaticAnalyzerCheckers.lib")
#pragma comment(lib,"clangStaticAnalyzerCore.lib")
#pragma comment(lib,"clangCrossTU.lib")
#pragma comment(lib,"clangIndex.lib")
#pragma comment(lib,"clangParse.lib")
#pragma comment(lib,"clangSema.lib")
#pragma comment(lib,"clangAnalysis.lib")
#pragma comment(lib,"clangASTMatchers.lib")
#pragma comment(lib,"clangEdit.lib")
#pragma comment(lib,"clangAST.lib")

#if _DEBUG
#pragma comment(lib,R"(FrontendTool\obj.clangFrontendTool.dir\Debug\obj.clangFrontendTool.lib)")
#pragma comment(lib,R"(ExtractAPI\obj.clangExtractAPI.dir\Debug\obj.clangExtractAPI.lib)")
#pragma comment(lib,R"(Sema\obj.clangSema.dir\Debug\obj.clangSema.lib)")
#pragma comment(lib,R"(CodeGen\obj.clangCodeGen.dir\Debug\obj.clangCodeGen.lib)")
#pragma comment(lib,R"(Support\obj.clangSupport.dir\Debug\obj.clangSupport.lib)")
#else
#pragma comment(lib,R"(FrontendTool\obj.clangFrontendTool.dir\Release\obj.clangFrontendTool.lib)")
#pragma comment(lib,R"(ExtractAPI\obj.clangExtractAPI.dir\Release\obj.clangExtractAPI.lib)")
#pragma comment(lib,R"(Sema\obj.clangSema.dir\Release\obj.clangSema.lib)")
#pragma comment(lib,R"(CodeGen\obj.clangCodeGen.dir\Release\obj.clangCodeGen.lib)")
#pragma comment(lib,R"(Support\obj.clangSupport.dir\Release\obj.clangSupport.lib)")
#endif

//!@ /*新生联创®（上海）*/
//!@ /*Mon Mar 15 09:32:21 UTC+0800 2021*/
//!@ /*___www.skstu.com___*/
#endif /*AFX_SK_H__80671DE0_DF45_4508_8EC6_DE5B285CC55E__HEAD__*/
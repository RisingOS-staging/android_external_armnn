//
// Copyright © 2017 Arm Ltd and Contributors. All rights reserved.
// SPDX-License-Identifier: MIT
//

#include "ClContextControlFixture.hpp"
#include "ClWorkloadFactoryHelper.hpp"

#include "test/TensorHelpers.hpp"
#include "test/UnitTests.hpp"

#include <cl/ClLayerSupport.hpp>
#include <cl/ClWorkloadFactory.hpp>
#include <cl/workloads/ClWorkloadUtils.hpp>

#include <backendsCommon/test/ActivationFixture.hpp>
#include <backendsCommon/test/LayerTests.hpp>

#include <arm_compute/core/CL/CLKernelLibrary.h>
#include <arm_compute/runtime/CL/CLScheduler.h>

#include <boost/test/unit_test.hpp>

#include <iostream>
#include <string>

BOOST_FIXTURE_TEST_SUITE(Compute_ArmComputeCl, ClContextControlFixture)

using namespace armnn;

using FactoryType = ClWorkloadFactory;

// ============================================================================
// UNIT tests

// Activation
ARMNN_AUTO_TEST_CASE(ConstantLinearActivation, ConstantLinearActivationTest)

// Sigmoid Activation / Logistic
ARMNN_AUTO_TEST_CASE(SimpleSigmoid, SimpleSigmoidTest)
ARMNN_AUTO_TEST_CASE(SimpleSigmoidUint8, SimpleSigmoidUint8Test)

// BoundedReLU Activation
ARMNN_AUTO_TEST_CASE(ReLu1, BoundedReLuUpperAndLowerBoundTest)
ARMNN_AUTO_TEST_CASE(ReLu6, BoundedReLuUpperBoundOnlyTest)
ARMNN_AUTO_TEST_CASE(ReLu1Uint8, BoundedReLuUint8UpperAndLowerBoundTest)
ARMNN_AUTO_TEST_CASE(ReLu6Uint8, BoundedReLuUint8UpperBoundOnlyTest)

// ReLU Activation
ARMNN_AUTO_TEST_CASE(ReLu, ReLuTest)
ARMNN_AUTO_TEST_CASE(ReLuUint8, ReLuUint8Test)

// SoftReLU Activation
ARMNN_AUTO_TEST_CASE(SoftReLu, SoftReLuTest)

// LeakyReLU Activation
ARMNN_AUTO_TEST_CASE(LeakyReLu, LeakyReLuTest)

// Abs Activation
ARMNN_AUTO_TEST_CASE(Abs, AbsTest)

// Sqrt Activation
ARMNN_AUTO_TEST_CASE(Sqrt, SqrtTest)
ARMNN_AUTO_TEST_CASE(SqrtNN, SqrtNNTest)

// Square Activation
ARMNN_AUTO_TEST_CASE(Square, SquareTest)

// Tanh Activation
ARMNN_AUTO_TEST_CASE(Tanh, TanhTest)

// Elu Activation
ARMNN_AUTO_TEST_CASE(Elu, EluTest)

// Batch To Space
ARMNN_AUTO_TEST_CASE(BatchToSpaceNdNhwcFloat321, BatchToSpaceNdNhwcTest1<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(BatchToSpaceNdNhwcFloat322, BatchToSpaceNdNhwcTest2<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(BatchToSpaceNdNhwcFloat323, BatchToSpaceNdNhwcTest3<DataType::Float32>)

ARMNN_AUTO_TEST_CASE(BatchToSpaceNdNchwFloat321, BatchToSpaceNdNchwTest1<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(BatchToSpaceNdNchwFloat322, BatchToSpaceNdNchwTest2<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(BatchToSpaceNdNchwFloat323, BatchToSpaceNdNchwTest3<DataType::Float32>)

ARMNN_AUTO_TEST_CASE(BatchToSpaceNdNhwcInt1, BatchToSpaceNdNhwcTest1<DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(BatchToSpaceNdNhwcInt2, BatchToSpaceNdNhwcTest2<DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(BatchToSpaceNdNhwcInt3, BatchToSpaceNdNhwcTest3<DataType::QAsymmS8>)

ARMNN_AUTO_TEST_CASE(BatchToSpaceNdNchwInt1, BatchToSpaceNdNchwTest1<DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(BatchToSpaceNdNchwInt2, BatchToSpaceNdNchwTest2<DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(BatchToSpaceNdNchwInt3, BatchToSpaceNdNchwTest3<DataType::QAsymmS8>)

ARMNN_AUTO_TEST_CASE(BatchToSpaceNdNhwcUint1, BatchToSpaceNdNhwcTest1<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(BatchToSpaceNdNhwcUint2, BatchToSpaceNdNhwcTest2<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(BatchToSpaceNdNhwcUint3, BatchToSpaceNdNhwcTest3<DataType::QAsymmU8>)

ARMNN_AUTO_TEST_CASE(BatchToSpaceNdNchwUint1, BatchToSpaceNdNchwTest1<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(BatchToSpaceNdNchwUint2, BatchToSpaceNdNchwTest2<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(BatchToSpaceNdNchwUint3, BatchToSpaceNdNchwTest3<DataType::QAsymmU8>)

// Fully Connected
ARMNN_AUTO_TEST_CASE(SimpleFullyConnected, FullyConnectedFloat32Test, false, false)
ARMNN_AUTO_TEST_CASE(SimpleFullyConnectedWithBias, FullyConnectedFloat32Test, true, false)
ARMNN_AUTO_TEST_CASE(SimpleFullyConnectedWithTranspose, FullyConnectedFloat32Test, false, true)
ARMNN_AUTO_TEST_CASE(FullyConnectedUint8, FullyConnectedTest<DataType::QAsymmU8>, false)
ARMNN_AUTO_TEST_CASE(FullyConnectedBiasedUint8, FullyConnectedTest<DataType::QAsymmU8>, true)

ARMNN_AUTO_TEST_CASE(FullyConnectedLarge, FullyConnectedLargeTest, false)
ARMNN_AUTO_TEST_CASE(FullyConnectedLargeTransposed, FullyConnectedLargeTest, true)

// Convolution
ARMNN_AUTO_TEST_CASE(SimpleConvolution1d, Convolution1dTest, true)

ARMNN_AUTO_TEST_CASE(SimpleConvolution2d, SimpleConvolution2d3x5Test, true, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleConvolution2dNhwc, SimpleConvolution2d3x5Test, true, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleConvolution2d3x3Uint8, SimpleConvolution2d3x3Uint8Test, true, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleConvolution2d3x3Uint8Nhwc, SimpleConvolution2d3x3Uint8Test, true, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(UnbiasedConvolution2d, SimpleConvolution2d3x5Test, false, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedConvolution2dNhwc, SimpleConvolution2d3x5Test, false, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(UnbiasedConvolution2dStride2x2Nhwc,
                     SimpleConvolution2d3x3Stride2x2Test, false, DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(UnbiasedConvolution2dSquare, SimpleConvolution2d3x3Test, false, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleConvolution2dAsymmetricPadding, Convolution2dAsymmetricPaddingTest, DataLayout::NCHW)

ARMNN_AUTO_TEST_CASE(UnbiasedConvolution2dSquareNhwc, SimpleConvolution2d3x3Test, false, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleConvolution2dAsymmetricPaddingNhwc,
                     Convolution2dAsymmetricPaddingTest,
                     DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(SimpleConvolution2dSquareNhwc, SimpleConvolution2d3x3NhwcTest, false)

ARMNN_AUTO_TEST_CASE(Convolution2d3x3Dilation3x3,
                     Convolution2d3x3Dilation3x3Test<DataType::Float32, DataType::Float32>,
                     false,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(Convolution2d3x3Dilation3x3Nhwc,
                     Convolution2d3x3Dilation3x3Test<DataType::Float32, DataType::Float32>,
                     false,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(Convolution2d3x3Dilation3x3Uint8,
                     Convolution2d3x3Dilation3x3Test<DataType::QAsymmU8, DataType::Signed32>,
                     false,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(Convolution2d3x3Dilation3x3NhwcUint8,
                     Convolution2d3x3Dilation3x3Test<DataType::QAsymmU8, DataType::Signed32>,
                     false,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(Convolution2d2x3x3Dilation3x3,
                     Convolution2d2x3x3Dilation3x3Test<DataType::Float32, DataType::Float32>,
                     false,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(Convolution2d2x3x3Dilation3x3Nhwc,
                     Convolution2d2x3x3Dilation3x3Test<DataType::Float32, DataType::Float32>,
                     false,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(Convolution2d2x3x3Dilation3x3Uint8,
                     Convolution2d2x3x3Dilation3x3Test<DataType::QAsymmU8, DataType::Signed32>,
                     false,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(Convolution2d2x3x3Dilation3x3NhwcUint8,
                     Convolution2d2x3x3Dilation3x3Test<DataType::QAsymmU8, DataType::Signed32>,
                     false,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(Convolution2d2x2Dilation2x2Padding2x2Stride3x3,
                     Convolution2d2x2Dilation2x2Padding2x2Stride3x3Test<DataType::Float32, DataType::Float32>,
                     false,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(Convolution2d2x2Dilation2x2Padding2x2Stride3x3Nhwc,
                     Convolution2d2x2Dilation2x2Padding2x2Stride3x3Test<DataType::Float32, DataType::Float32>,
                     false,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(Convolution2d2x2Dilation2x2Padding2x2Stride3x3Uint8,
                     Convolution2d2x2Dilation2x2Padding2x2Stride3x3Test<DataType::QAsymmU8, DataType::Signed32>,
                     false,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(Convolution2d2x2Dilation2x2Padding2x2Stride3x3NhwcUint8,
                     Convolution2d2x2Dilation2x2Padding2x2Stride3x3Test<DataType::QAsymmU8, DataType::Signed32>,
                     false,
                     DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(Convolution2dPerAxisQuantTestNchw, Convolution2dPerAxisQuantTest, DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(Convolution2dPerAxisQuantTestNhwc, Convolution2dPerAxisQuantTest, DataLayout::NHWC);

// Depthwise Convolution
ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dDepthMul1,
                     DepthwiseConvolution2dDepthMul1Test, true, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedDepthwiseConvolution2dDepthMul1,
                     DepthwiseConvolution2dDepthMul1Test, false, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dDepthMul1Uint8,
                     DepthwiseConvolution2dDepthMul1Uint8Test, true, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedDepthwiseConvolution2dDepthMul1Uint8,
                     DepthwiseConvolution2dDepthMul1Uint8Test, false, DataLayout::NCHW)

// NHWC Depthwise Convolution
ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dDepthMul1Nhwc,
                     DepthwiseConvolution2dDepthMul1Test, true, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(UnbiasedDepthwiseConvolution2dDepthMul1Nhwc,
                     DepthwiseConvolution2dDepthMul1Test, false, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dDepthMul1Uint8Nhwc,
                     DepthwiseConvolution2dDepthMul1Uint8Test, true, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(UnbiasedDepthwiseConvolution2dDepthMul1Uint8Nhwc,
                     DepthwiseConvolution2dDepthMul1Uint8Test, false, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleDepthwiseConvolution2d3x3Dilation3x3Nhwc,
                     SimpleDepthwiseConvolution2d3x3Dilation3x3NhwcTest)


ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dDepthNhwc, DepthwiseConvolution2dDepthNhwcTest, false)

ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dAsymmetric,
                     DepthwiseConvolution2dAsymmetricTest, true, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedDepthwiseConvolution2dAsymmetric,
                     DepthwiseConvolution2dAsymmetricTest, false, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dAsymmetricNhwc,
                     DepthwiseConvolution2dAsymmetricTest, true, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(UnbiasedDepthwiseConvolution2dAsymmetricNhwc,
                     DepthwiseConvolution2dAsymmetricTest, false, DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dDepthMul64, DepthwiseConvolution2dDepthMul64Test);

ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dPerAxisQuantTestNchw, DepthwiseConvolution2dPerAxisQuantTest,
                     DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(DepthwiseConvolution2dPerAxisQuantTestNhwc, DepthwiseConvolution2dPerAxisQuantTest,
                     DataLayout::NHWC);

// Splitter
ARMNN_AUTO_TEST_CASE(SimpleSplitterFloat32, SplitterFloat32Test)
ARMNN_AUTO_TEST_CASE(SimpleSplitterUint8, SplitterUint8Test)

ARMNN_AUTO_TEST_CASE(CopyViaSplitterFloat32, CopyViaSplitterFloat32Test)
ARMNN_AUTO_TEST_CASE(CopyViaSplitterUint8, CopyViaSplitterUint8Test)

// Concat
ARMNN_AUTO_TEST_CASE(SimpleConcat, ConcatTest)
ARMNN_AUTO_TEST_CASE(ConcatUint8, ConcatUint8Test)
ARMNN_AUTO_TEST_CASE(ConcatUint8DifferentInputOutputQParam,
                     ConcatDifferentInputOutputQParamTest<DataType::QAsymmU8>, false)

// Normalization
ARMNN_AUTO_TEST_CASE(SimpleNormalizationAcross, SimpleNormalizationAcrossTest)
ARMNN_AUTO_TEST_CASE(SimpleNormalizationWithin, SimpleNormalizationWithinTest)
ARMNN_AUTO_TEST_CASE(SimpleNormalizationAcrossNhwc, SimpleNormalizationAcrossNhwcTest)

// Pooling
ARMNN_AUTO_TEST_CASE(SimpleMaxPooling2dSize3x3Stride2x4, SimpleMaxPooling2dSize3x3Stride2x4Test, true)
ARMNN_AUTO_TEST_CASE(SimpleMaxPooling2dSize3x3Stride2x4Uint8, SimpleMaxPooling2dSize3x3Stride2x4Uint8Test, true)

ARMNN_AUTO_TEST_CASE(IgnorePaddingSimpleMaxPooling2d, IgnorePaddingSimpleMaxPooling2dTest)
ARMNN_AUTO_TEST_CASE(IgnorePaddingSimpleMaxPooling2dUint8, IgnorePaddingSimpleMaxPooling2dUint8Test)
ARMNN_AUTO_TEST_CASE(IgnorePaddingMaxPooling2dSize3, IgnorePaddingMaxPooling2dSize3Test)
ARMNN_AUTO_TEST_CASE(IgnorePaddingMaxPooling2dSize3Uint8, IgnorePaddingMaxPooling2dSize3Uint8Test)

ARMNN_AUTO_TEST_CASE(IgnorePaddingSimpleAveragePooling2d, IgnorePaddingSimpleAveragePooling2dTest)
ARMNN_AUTO_TEST_CASE(IgnorePaddingSimpleAveragePooling2dUint8, IgnorePaddingSimpleAveragePooling2dUint8Test)
ARMNN_AUTO_TEST_CASE(IgnorePaddingSimpleAveragePooling2dNoPadding, IgnorePaddingSimpleAveragePooling2dNoPaddingTest)
ARMNN_AUTO_TEST_CASE(IgnorePaddingSimpleAveragePooling2dNoPaddingUint8,
                     IgnorePaddingSimpleAveragePooling2dNoPaddingUint8Test)
ARMNN_AUTO_TEST_CASE(IgnorePaddingAveragePooling2dSize3, IgnorePaddingAveragePooling2dSize3Test)
ARMNN_AUTO_TEST_CASE(IgnorePaddingAveragePooling2dSize3Uint8, IgnorePaddingAveragePooling2dSize3Uint8Test)

ARMNN_AUTO_TEST_CASE(IgnorePaddingSimpleL2Pooling2d, IgnorePaddingSimpleL2Pooling2dTest)
ARMNN_AUTO_TEST_CASE(UNSUPPORTED_IgnorePaddingSimpleL2Pooling2dUint8, IgnorePaddingSimpleL2Pooling2dUint8Test)
ARMNN_AUTO_TEST_CASE(IgnorePaddingL2Pooling2dSize3, IgnorePaddingL2Pooling2dSize3Test)
ARMNN_AUTO_TEST_CASE(UNSUPPORTED_IgnorePaddingL2Pooling2dSize3Uint8, IgnorePaddingL2Pooling2dSize3Uint8Test)

ARMNN_AUTO_TEST_CASE(SimpleMaxPooling2d, SimpleMaxPooling2dTest, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleMaxPooling2dNhwc, SimpleMaxPooling2dTest, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleMaxPooling2dUint8, SimpleMaxPooling2dUint8Test, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleMaxPooling2dUint8Nhwc, SimpleMaxPooling2dUint8Test, DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(SimpleAveragePooling2d, SimpleAveragePooling2dTest, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleAveragePooling2dNhwc, SimpleAveragePooling2dTest, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleAveragePooling2dUint8, SimpleAveragePooling2dUint8Test, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleAveragePooling2dUint8Nhwc, SimpleAveragePooling2dUint8Test, DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(IgnorePaddingAveragePooling2dSize3x2Stride2x2,
                     IgnorePaddingAveragePooling2dSize3x2Stride2x2Test,
                     false)
ARMNN_AUTO_TEST_CASE(IgnorePaddingAveragePooling2dSize3x2Stride2x2NoPadding,
                     IgnorePaddingAveragePooling2dSize3x2Stride2x2Test,
                     true)
ARMNN_AUTO_TEST_CASE(LargeTensorsAveragePooling2d, LargeTensorsAveragePooling2dTest)
ARMNN_AUTO_TEST_CASE(LargeTensorsAveragePooling2dUint8, LargeTensorsAveragePooling2dUint8Test)

ARMNN_AUTO_TEST_CASE(SimpleL2Pooling2d, SimpleL2Pooling2dTest, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleL2Pooling2dNhwc, SimpleL2Pooling2dTest, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(UNSUPPORTED_SimpleL2Pooling2dUint8, SimpleL2Pooling2dUint8Test, DataLayout::NCHW)

ARMNN_AUTO_TEST_CASE(L2Pooling2dSize3Stride1, L2Pooling2dSize3Stride1Test)
ARMNN_AUTO_TEST_CASE(UNSUPPORTED_L2Pooling2dSize3Stride1Uint8, L2Pooling2dSize3Stride1Uint8Test)
ARMNN_AUTO_TEST_CASE(L2Pooling2dSize3Stride3, L2Pooling2dSize3Stride3Test)
ARMNN_AUTO_TEST_CASE(UNSUPPORTED_L2Pooling2dSize3Stride3Uint8, L2Pooling2dSize3Stride3Uint8Test)
ARMNN_AUTO_TEST_CASE(L2Pooling2dSize3Stride4, L2Pooling2dSize3Stride4Test)
ARMNN_AUTO_TEST_CASE(UNSUPPORTED_L2Pooling2dSize3Stride4Uint8, L2Pooling2dSize3Stride4Uint8Test)
ARMNN_AUTO_TEST_CASE(L2Pooling2dSize7, L2Pooling2dSize7Test)
ARMNN_AUTO_TEST_CASE(UNSUPPORTED_L2Pooling2dSize7Uint8, L2Pooling2dSize7Uint8Test)
ARMNN_AUTO_TEST_CASE(L2Pooling2dSize9, L2Pooling2dSize9Test)
ARMNN_AUTO_TEST_CASE(UNSUPPORTED_L2Pooling2dSize9Uint8, L2Pooling2dSize9Uint8Test)

// Add
ARMNN_AUTO_TEST_CASE(SimpleAdd, AdditionTest)
ARMNN_AUTO_TEST_CASE(Add5d, Addition5dTest)
ARMNN_AUTO_TEST_CASE(AddBroadcast1Element, AdditionBroadcast1ElementTest)
ARMNN_AUTO_TEST_CASE(AddBroadcast, AdditionBroadcastTest)

ARMNN_AUTO_TEST_CASE(AdditionUint8, AdditionUint8Test)
ARMNN_AUTO_TEST_CASE(AddBroadcastUint8, AdditionBroadcastUint8Test)
ARMNN_AUTO_TEST_CASE(AddBroadcast1ElementUint8, AdditionBroadcast1ElementUint8Test)

// Sub
ARMNN_AUTO_TEST_CASE(SimpleSub, SubtractionTest)
ARMNN_AUTO_TEST_CASE(SubBroadcast1Element, SubtractionBroadcast1ElementTest)
ARMNN_AUTO_TEST_CASE(SubBroadcast, SubtractionBroadcastTest)

ARMNN_AUTO_TEST_CASE(SubtractionUint8, SubtractionUint8Test)
ARMNN_AUTO_TEST_CASE(SubBroadcastUint8, SubtractionBroadcastUint8Test)
ARMNN_AUTO_TEST_CASE(SubBroadcast1ElementUint8, SubtractionBroadcast1ElementUint8Test)

// Div
ARMNN_AUTO_TEST_CASE(SimpleDivision, DivisionTest)
ARMNN_AUTO_TEST_CASE(DivisionByZero, DivisionByZeroTest)
ARMNN_AUTO_TEST_CASE(DivisionBroadcast1Element, DivisionBroadcast1ElementTest)
ARMNN_AUTO_TEST_CASE(DivisionBroadcast1DVector, DivisionBroadcast1DVectorTest)
// NOTE: quantized division is not supported by CL and not required by the
//       android NN api

// Mul
ARMNN_AUTO_TEST_CASE(SimpleMultiplication, MultiplicationTest)
ARMNN_AUTO_TEST_CASE(MultiplicationBroadcast1Element, MultiplicationBroadcast1ElementTest)
ARMNN_AUTO_TEST_CASE(MultiplicationBroadcast1DVector, MultiplicationBroadcast1DVectorTest)
ARMNN_AUTO_TEST_CASE(MultiplicationUint8, MultiplicationUint8Test)
ARMNN_AUTO_TEST_CASE(MultiplicationBroadcast1ElementUint8, MultiplicationBroadcast1ElementUint8Test)
ARMNN_AUTO_TEST_CASE(MultiplicationBroadcast1DVectorUint8, MultiplicationBroadcast1DVectorUint8Test)
ARMNN_AUTO_TEST_CASE(Multiplication5d, Multiplication5dTest)

// Batch Norm
ARMNN_AUTO_TEST_CASE(BatchNormFloat32, BatchNormFloat32Test)
ARMNN_AUTO_TEST_CASE(BatchNormFloat32Nhwc, BatchNormFloat32NhwcTest)

// InstanceNormalization
ARMNN_AUTO_TEST_CASE(InstanceNormFloat32Nchw, InstanceNormFloat32Test, DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(InstanceNormFloat16Nchw, InstanceNormFloat16Test, DataLayout::NCHW);

ARMNN_AUTO_TEST_CASE(InstanceNormFloat32Nhwc, InstanceNormFloat32Test, DataLayout::NHWC);
ARMNN_AUTO_TEST_CASE(InstanceNormFloat16Nhwc, InstanceNormFloat16Test, DataLayout::NHWC);

ARMNN_AUTO_TEST_CASE(InstanceNormFloat32Nchw2, InstanceNormFloat32Test2, DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(InstanceNormFloat16Nchw2, InstanceNormFloat16Test2, DataLayout::NCHW);

ARMNN_AUTO_TEST_CASE(InstanceNormFloat32Nhwc2, InstanceNormFloat32Test2, DataLayout::NHWC);
ARMNN_AUTO_TEST_CASE(InstanceNormFloat16Nhwc2, InstanceNormFloat16Test2, DataLayout::NHWC);

// L2 Normalization
ARMNN_AUTO_TEST_CASE(L2Normalization1d, L2Normalization1dTest, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(L2Normalization2d, L2Normalization2dTest, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(L2Normalization3d, L2Normalization3dTest, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(L2Normalization4d, L2Normalization4dTest, DataLayout::NCHW)

ARMNN_AUTO_TEST_CASE(L2Normalization1dNhwc, L2Normalization1dTest, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(L2Normalization2dNhwc, L2Normalization2dTest, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(L2Normalization3dNhwc, L2Normalization3dTest, DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(L2Normalization4dNhwc, L2Normalization4dTest, DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(L2Normalization2dShape, L2Normalization2dShapeTest);

ARMNN_AUTO_TEST_CASE(L2NormalizationDefaultEpsilon, L2NormalizationDefaultEpsilonTest, DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(L2NormalizationNonDefaultEpsilon, L2NormalizationNonDefaultEpsilonTest, DataLayout::NCHW)

// Constant
ARMNN_AUTO_TEST_CASE(Constant, ConstantTest)
ARMNN_AUTO_TEST_CASE(ConstantUint8, ConstantUint8SimpleQuantizationScaleNoOffsetTest)

// Concat
ARMNN_AUTO_TEST_CASE(Concat1d, Concat1dTest)
ARMNN_AUTO_TEST_CASE(Concat1dUint8, Concat1dUint8Test)

ARMNN_AUTO_TEST_CASE(Concat2dDim0, Concat2dDim0Test)
ARMNN_AUTO_TEST_CASE(Concat2dDim0Uint8, Concat2dDim0Uint8Test)
ARMNN_AUTO_TEST_CASE(Concat2dDim1, Concat2dDim1Test)
ARMNN_AUTO_TEST_CASE(Concat2dDim1Uint8, Concat2dDim1Uint8Test)

ARMNN_AUTO_TEST_CASE(Concat2dDim0DiffInputDims, Concat2dDim0DiffInputDimsTest)
ARMNN_AUTO_TEST_CASE(Concat2dDim0DiffInputDimsUint8, Concat2dDim0DiffInputDimsUint8Test)
ARMNN_AUTO_TEST_CASE(Concat2dDim1DiffInputDims, Concat2dDim1DiffInputDimsTest)
ARMNN_AUTO_TEST_CASE(Concat2dDim1DiffInputDimsUint8, Concat2dDim1DiffInputDimsUint8Test)

ARMNN_AUTO_TEST_CASE(Concat3dDim0, Concat3dDim0Test)
ARMNN_AUTO_TEST_CASE(Concat3dDim0Uint8, Concat3dDim0Uint8Test)
ARMNN_AUTO_TEST_CASE(Concat3dDim1, Concat3dDim1Test)
ARMNN_AUTO_TEST_CASE(Concat3dDim1Uint8, Concat3dDim1Uint8Test)
ARMNN_AUTO_TEST_CASE(Concat3dDim2, Concat3dDim2Test, false)
ARMNN_AUTO_TEST_CASE(Concat3dDim2Uint8, Concat3dDim2Uint8Test, false)

ARMNN_AUTO_TEST_CASE(Concat3dDim0DiffInputDims, Concat3dDim0DiffInputDimsTest)
ARMNN_AUTO_TEST_CASE(Concat3dDim0DiffInputDimsUint8, Concat3dDim0DiffInputDimsUint8Test)
ARMNN_AUTO_TEST_CASE(Concat3dDim1DiffInputDims, Concat3dDim1DiffInputDimsTest)
ARMNN_AUTO_TEST_CASE(Concat3dDim1DiffInputDimsUint8, Concat3dDim1DiffInputDimsUint8Test)
ARMNN_AUTO_TEST_CASE(Concat3dDim2DiffInputDims, Concat3dDim2DiffInputDimsTest, false)
ARMNN_AUTO_TEST_CASE(Concat3dDim2DiffInputDimsUint8, Concat3dDim2DiffInputDimsUint8Test, false)

ARMNN_AUTO_TEST_CASE(Concat4dDim0, Concat4dDim0Test)
ARMNN_AUTO_TEST_CASE(Concat4dDim1, Concat4dDim1Test)
ARMNN_AUTO_TEST_CASE(Concat4dDim3, Concat4dDim3Test, false)
ARMNN_AUTO_TEST_CASE(Concat4dDim0Uint8, Concat4dDim0Uint8Test)
ARMNN_AUTO_TEST_CASE(Concat4dDim1Uint8, Concat4dDim1Uint8Test)
ARMNN_AUTO_TEST_CASE(Concat4dDim3Uint8, Concat4dDim3Uint8Test, false)

ARMNN_AUTO_TEST_CASE(Concat4dDiffShapeDim0, Concat4dDiffShapeDim0Test)
ARMNN_AUTO_TEST_CASE(Concat4dDiffShapeDim1, Concat4dDiffShapeDim1Test)
ARMNN_AUTO_TEST_CASE(Concat4dDiffShapeDim3, Concat4dDiffShapeDim3Test, false)
ARMNN_AUTO_TEST_CASE(Concat4dDiffShapeDim0Uint8, Concat4dDiffShapeDim0Uint8Test)
ARMNN_AUTO_TEST_CASE(Concat4dDiffShapeDim1Uint8, Concat4dDiffShapeDim1Uint8Test)
ARMNN_AUTO_TEST_CASE(Concat4dDiffShapeDim3Uint8, Concat4dDiffShapeDim3Uint8Test, false)

// DepthToSpace
ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwFloat32_1, DepthToSpaceTest1<DataType::Float32>, DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwFloat32_2, DepthToSpaceTest2<DataType::Float32>, DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwFloat32_3, DepthToSpaceTest3<DataType::Float32>, DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwFloat32_4, DepthToSpaceTest4<DataType::Float32>, DataLayout::NCHW);

ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwFloat16_1, DepthToSpaceTest1<DataType::Float16>, DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwFloat16_2, DepthToSpaceTest2<DataType::Float16>, DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwFloat16_3, DepthToSpaceTest3<DataType::Float16>, DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwFloat16_4, DepthToSpaceTest4<DataType::Float16>, DataLayout::NCHW);

ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwInt8_1, DepthToSpaceTest1<DataType::QAsymmS8>, DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwInt8_2, DepthToSpaceTest2<DataType::QAsymmS8>, DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwInt8_3, DepthToSpaceTest3<DataType::QAsymmS8>, DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwInt8_4, DepthToSpaceTest4<DataType::QAsymmS8>, DataLayout::NCHW);

ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwUint8_1, DepthToSpaceTest1<DataType::QAsymmU8>, DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwUint8_2, DepthToSpaceTest2<DataType::QAsymmU8>, DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwUint8_3, DepthToSpaceTest3<DataType::QAsymmU8>, DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwUint8_4, DepthToSpaceTest4<DataType::QAsymmU8>, DataLayout::NCHW);

ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwInt16_1, DepthToSpaceTest1<DataType::QSymmS16>, DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwInt16_2, DepthToSpaceTest2<DataType::QSymmS16>, DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwInt16_3, DepthToSpaceTest3<DataType::QSymmS16>, DataLayout::NCHW);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNchwInt16_4, DepthToSpaceTest4<DataType::QSymmS16>, DataLayout::NCHW);

ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcFloat32_1, DepthToSpaceTest1<DataType::Float32>, DataLayout::NHWC);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcFloat32_2, DepthToSpaceTest2<DataType::Float32>, DataLayout::NHWC);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcFloat32_3, DepthToSpaceTest3<DataType::Float32>, DataLayout::NHWC);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcFloat32_4, DepthToSpaceTest4<DataType::Float32>, DataLayout::NHWC);

ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcFloat16_1, DepthToSpaceTest1<DataType::Float16>, DataLayout::NHWC);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcFloat16_2, DepthToSpaceTest2<DataType::Float16>, DataLayout::NHWC);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcFloat16_3, DepthToSpaceTest3<DataType::Float16>, DataLayout::NHWC);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcFloat16_4, DepthToSpaceTest4<DataType::Float16>, DataLayout::NHWC);

ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcInt8_1, DepthToSpaceTest1<DataType::QAsymmS8>, DataLayout::NHWC);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcInt8_2, DepthToSpaceTest2<DataType::QAsymmS8>, DataLayout::NHWC);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcInt8_3, DepthToSpaceTest3<DataType::QAsymmS8>, DataLayout::NHWC);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcInt8_4, DepthToSpaceTest4<DataType::QAsymmS8>, DataLayout::NHWC);

ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcUint8_1, DepthToSpaceTest1<DataType::QAsymmU8>, DataLayout::NHWC);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcUint8_2, DepthToSpaceTest2<DataType::QAsymmU8>, DataLayout::NHWC);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcUint8_3, DepthToSpaceTest3<DataType::QAsymmU8>, DataLayout::NHWC);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcUint8_4, DepthToSpaceTest4<DataType::QAsymmU8>, DataLayout::NHWC);

ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcInt16_1, DepthToSpaceTest1<DataType::QSymmS16>, DataLayout::NHWC);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcInt16_2, DepthToSpaceTest2<DataType::QSymmS16>, DataLayout::NHWC);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcInt16_3, DepthToSpaceTest3<DataType::QSymmS16>, DataLayout::NHWC);
ARMNN_AUTO_TEST_CASE(DepthToSpaceNhwcInt16_4, DepthToSpaceTest4<DataType::QSymmS16>, DataLayout::NHWC);

// Fill
ARMNN_AUTO_TEST_CASE_WITH_THF(SimpleFill, SimpleFillTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE_WITH_THF(SimpleFillF16, SimpleFillTest<DataType::Float16>)
ARMNN_AUTO_TEST_CASE_WITH_THF(SimpleFillS32, SimpleFillTest<DataType::Signed32>)

// Floor
ARMNN_AUTO_TEST_CASE(SimpleFloor, SimpleFloorTest<DataType::Float32>)

// Gather
ARMNN_AUTO_TEST_CASE(Gather1dParamsFloat32, Gather1dParamsFloat32Test)
ARMNN_AUTO_TEST_CASE(Gather1dParamsUint8, Gather1dParamsUint8Test)
ARMNN_AUTO_TEST_CASE(GatherMultiDimParamsFloat32, GatherMultiDimParamsFloat32Test)
ARMNN_AUTO_TEST_CASE(GatherMultiDimParamsUint8, GatherMultiDimParamsUint8Test)

// Reshape
ARMNN_AUTO_TEST_CASE(SimpleReshapeFloat32, SimpleReshapeTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(SimpleReshapeInt8, SimpleReshapeTest<DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(SimpleReshapeUint8, SimpleReshapeTest<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(Reshape5d, Reshape5dTest<DataType::Float32>)

// Pad
ARMNN_AUTO_TEST_CASE(PadFloat322d, PadFloat322dTest)
ARMNN_AUTO_TEST_CASE(PadFloat322dCustomPadding, PadFloat322dCustomPaddingTest)
ARMNN_AUTO_TEST_CASE(PadFloat323d, PadFloat323dTest)
ARMNN_AUTO_TEST_CASE(PadFloat324d, PadFloat324dTest)

ARMNN_AUTO_TEST_CASE(PadUint82d, PadUint82dTest)
ARMNN_AUTO_TEST_CASE(PadUint82dCustomPadding, PadUint82dCustomPaddingTest)
ARMNN_AUTO_TEST_CASE(PadUint83d, PadUint83dTest)
ARMNN_AUTO_TEST_CASE(PadUint84d, PadUint84dTest)

ARMNN_AUTO_TEST_CASE(Pad2dQSymm16, Pad2dTestCommon<DataType::QSymmS16>, 2.0f, 0, 0.0f)
ARMNN_AUTO_TEST_CASE(Pad2dQSymm16CustomPadding, Pad2dTestCommon<DataType::QSymmS16>, 2.0f, 0, 1.0f)
ARMNN_AUTO_TEST_CASE(Pad3dQSymm16, Pad3dTestCommon<DataType::QSymmS16>, 2.0f, 0)
ARMNN_AUTO_TEST_CASE(Pad4dQSymm16, Pad4dTestCommon<DataType::QSymmS16>, 2.0f, 0)

// PReLU
ARMNN_AUTO_TEST_CASE(PreluFloat32, PreluTest<ClWorkloadFactory, DataType::Float32>)
ARMNN_AUTO_TEST_CASE(PreluUint8,   PreluTest<ClWorkloadFactory, DataType::QAsymmU8>)

// Permute
ARMNN_AUTO_TEST_CASE(SimplePermuteFloat32, SimplePermuteTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(PermuteFloat32ValueSet1Test, PermuteValueSet1Test<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(PermuteFloat32ValueSet2Test, PermuteValueSet2Test<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(PermuteFloat32ValueSet3Test, PermuteValueSet3Test<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(SimplePermuteQASymmS8, SimplePermuteTest<DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(PermuteQASymmS8ValueSet1Test, PermuteValueSet1Test<DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(PermuteQASymmS8ValueSet2Test, PermuteValueSet2Test<DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(PermuteQASymmS8ValueSet3Test, PermuteValueSet3Test<DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(SimplePermuteQASymm8, SimplePermuteTest<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(PermuteQASymm8ValueSet1Test, PermuteValueSet1Test<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(PermuteQASymm8ValueSet2Test, PermuteValueSet2Test<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(PermuteQASymm8ValueSet3Test, PermuteValueSet3Test<DataType::QAsymmU8>)

// Lstm
ARMNN_AUTO_TEST_CASE(LstmLayerFloat32WithCifgWithPeepholeNoProjection,
                     LstmLayerFloat32WithCifgWithPeepholeNoProjectionTest)
ARMNN_AUTO_TEST_CASE(LstmLayerFloat32NoCifgNoPeepholeNoProjection,
                     LstmLayerFloat32NoCifgNoPeepholeNoProjectionTest)
ARMNN_AUTO_TEST_CASE(LstmLayerFloat32NoCifgWithPeepholeWithProjection,
                     LstmLayerFloat32NoCifgWithPeepholeWithProjectionTest)

ARMNN_AUTO_TEST_CASE(LstmLayerFloat32NoCifgWithPeepholeWithProjectionWithLayerNorm,
                     LstmLayerFloat32NoCifgWithPeepholeWithProjectionWithLayerNormTest)

// QLstm
ARMNN_AUTO_TEST_CASE(QLstm, QLstmTest)

// QuantizedLstm
ARMNN_AUTO_TEST_CASE(QuantizedLstm, QuantizedLstmTest)

// Convert from Float16 to Float32
ARMNN_AUTO_TEST_CASE(SimpleConvertFp16ToFp32, SimpleConvertFp16ToFp32Test)
// Convert from Float32 to Float16
ARMNN_AUTO_TEST_CASE(SimpleConvertFp32ToFp16, SimpleConvertFp32ToFp16Test)

ARMNN_AUTO_TEST_CASE(AdditionAfterMaxPool, AdditionAfterMaxPoolTest)

//Max
ARMNN_AUTO_TEST_CASE(MaximumSimple, MaximumSimpleTest)
ARMNN_AUTO_TEST_CASE(MaximumBroadcast1Element, MaximumBroadcast1ElementTest)
ARMNN_AUTO_TEST_CASE(MaximumBroadcast1DVector, MaximumBroadcast1DVectorTest)
ARMNN_AUTO_TEST_CASE(MaximumUint8, MaximumUint8Test)
ARMNN_AUTO_TEST_CASE(MaximumBroadcast1ElementUint8, MaximumBroadcast1ElementUint8Test)
ARMNN_AUTO_TEST_CASE(MaximumBroadcast1DVectorUint8, MaximumBroadcast1DVectorUint8Test)

// Mean
ARMNN_AUTO_TEST_CASE(MeanSimpleFloat32, MeanSimpleTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(MeanSimpleAxisFloat32, MeanSimpleAxisTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(MeanKeepDimsFloat32, MeanKeepDimsTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(MeanMultipleDimsFloat32, MeanMultipleDimsTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(MeanVts1Float32, MeanVts1Test<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(MeanVts2Float32, MeanVts2Test<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(MeanVts3Float32, MeanVts3Test<DataType::Float32>)

ARMNN_AUTO_TEST_CASE(MeanSimpleQuantisedAsymmS8, MeanSimpleTest<DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(MeanSimpleAxisQuantisedAsymmS8, MeanSimpleAxisTest<DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(MeanKeepDimsQuantisedAsymmS8, MeanKeepDimsTest<DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(MeanMultipleDimsQuantisedAsymmS8, MeanMultipleDimsTest<DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(MeanVts1QuantisedAsymmS8, MeanVts1Test<DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(MeanVts2QuantisedAsymmS8, MeanVts2Test<DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(MeanVts3QuantisedAsymmS8, MeanVts3Test<DataType::QAsymmS8>)

ARMNN_AUTO_TEST_CASE(MeanSimpleQuantisedAsymm8, MeanSimpleTest<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(MeanSimpleAxisQuantisedAsymm8, MeanSimpleAxisTest<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(MeanKeepDimsQuantisedAsymm8, MeanKeepDimsTest<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(MeanMultipleDimsQuantisedAsymm8, MeanMultipleDimsTest<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(MeanVts1QuantisedAsymm8, MeanVts1Test<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(MeanVts2QuantisedAsymm8, MeanVts2Test<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(MeanVts3QuantisedAsymm8, MeanVts3Test<DataType::QAsymmU8>)

// Minimum
ARMNN_AUTO_TEST_CASE(MinimumBroadcast1Element1, MinimumBroadcast1ElementTest1)
ARMNN_AUTO_TEST_CASE(MinimumBroadcast1Element2, MinimumBroadcast1ElementTest2)
ARMNN_AUTO_TEST_CASE(MinimumBroadcast1DVectorUint8, MinimumBroadcast1DVectorUint8Test)

// Equal
ARMNN_AUTO_TEST_CASE(EqualSimple,            EqualSimpleTest)
ARMNN_AUTO_TEST_CASE(EqualBroadcast1Element, EqualBroadcast1ElementTest)
ARMNN_AUTO_TEST_CASE(EqualBroadcast1dVector, EqualBroadcast1dVectorTest)

ARMNN_AUTO_TEST_CASE(EqualSimpleFloat16,            EqualSimpleFloat16Test)
ARMNN_AUTO_TEST_CASE(EqualBroadcast1ElementFloat16, EqualBroadcast1ElementFloat16Test)
ARMNN_AUTO_TEST_CASE(EqualBroadcast1dVectorFloat16, EqualBroadcast1dVectorFloat16Test)

ARMNN_AUTO_TEST_CASE(EqualSimpleUint8,            EqualSimpleUint8Test)
ARMNN_AUTO_TEST_CASE(EqualBroadcast1ElementUint8, EqualBroadcast1ElementUint8Test)
ARMNN_AUTO_TEST_CASE(EqualBroadcast1dVectorUint8, EqualBroadcast1dVectorUint8Test)

// Greater
ARMNN_AUTO_TEST_CASE(GreaterSimple,            GreaterSimpleTest)
ARMNN_AUTO_TEST_CASE(GreaterBroadcast1Element, GreaterBroadcast1ElementTest)
ARMNN_AUTO_TEST_CASE(GreaterBroadcast1dVector, GreaterBroadcast1dVectorTest)

ARMNN_AUTO_TEST_CASE(GreaterSimpleFloat16,            GreaterSimpleFloat16Test)
ARMNN_AUTO_TEST_CASE(GreaterBroadcast1ElementFloat16, GreaterBroadcast1ElementFloat16Test)
ARMNN_AUTO_TEST_CASE(GreaterBroadcast1dVectorFloat16, GreaterBroadcast1dVectorFloat16Test)

ARMNN_AUTO_TEST_CASE(GreaterSimpleUint8,            GreaterSimpleUint8Test)
ARMNN_AUTO_TEST_CASE(GreaterBroadcast1ElementUint8, GreaterBroadcast1ElementUint8Test)
ARMNN_AUTO_TEST_CASE(GreaterBroadcast1dVectorUint8, GreaterBroadcast1dVectorUint8Test)

// GreaterOrEqual
ARMNN_AUTO_TEST_CASE(GreaterOrEqualSimple,            GreaterOrEqualSimpleTest)
ARMNN_AUTO_TEST_CASE(GreaterOrEqualBroadcast1Element, GreaterOrEqualBroadcast1ElementTest)
ARMNN_AUTO_TEST_CASE(GreaterOrEqualBroadcast1dVector, GreaterOrEqualBroadcast1dVectorTest)

ARMNN_AUTO_TEST_CASE(GreaterOrEqualSimpleFloat16,            GreaterOrEqualSimpleFloat16Test)
ARMNN_AUTO_TEST_CASE(GreaterOrEqualBroadcast1ElementFloat16, GreaterOrEqualBroadcast1ElementFloat16Test)
ARMNN_AUTO_TEST_CASE(GreaterOrEqualBroadcast1dVectorFloat16, GreaterOrEqualBroadcast1dVectorFloat16Test)

ARMNN_AUTO_TEST_CASE(GreaterOrEqualSimpleUint8,            GreaterOrEqualSimpleUint8Test)
ARMNN_AUTO_TEST_CASE(GreaterOrEqualBroadcast1ElementUint8, GreaterOrEqualBroadcast1ElementUint8Test)
ARMNN_AUTO_TEST_CASE(GreaterOrEqualBroadcast1dVectorUint8, GreaterOrEqualBroadcast1dVectorUint8Test)

// Less
ARMNN_AUTO_TEST_CASE(LessSimple,            LessSimpleTest)
ARMNN_AUTO_TEST_CASE(LessBroadcast1Element, LessBroadcast1ElementTest)
ARMNN_AUTO_TEST_CASE(LessBroadcast1dVector, LessBroadcast1dVectorTest)

ARMNN_AUTO_TEST_CASE(LessSimpleFloat16,            LessSimpleFloat16Test)
ARMNN_AUTO_TEST_CASE(LessBroadcast1ElementFloat16, LessBroadcast1ElementFloat16Test)
ARMNN_AUTO_TEST_CASE(LessBroadcast1dVectorFloat16, LessBroadcast1dVectorFloat16Test)

ARMNN_AUTO_TEST_CASE(LessSimpleUint8,            LessSimpleUint8Test)
ARMNN_AUTO_TEST_CASE(LessBroadcast1ElementUint8, LessBroadcast1ElementUint8Test)
ARMNN_AUTO_TEST_CASE(LessBroadcast1dVectorUint8, LessBroadcast1dVectorUint8Test)

// LessOrEqual
ARMNN_AUTO_TEST_CASE(LessOrEqualSimple,            LessOrEqualSimpleTest)
ARMNN_AUTO_TEST_CASE(LessOrEqualBroadcast1Element, LessOrEqualBroadcast1ElementTest)
ARMNN_AUTO_TEST_CASE(LessOrEqualBroadcast1dVector, LessOrEqualBroadcast1dVectorTest)

ARMNN_AUTO_TEST_CASE(LessOrEqualSimpleFloat16,            LessOrEqualSimpleFloat16Test)
ARMNN_AUTO_TEST_CASE(LessOrEqualBroadcast1ElementFloat16, LessOrEqualBroadcast1ElementFloat16Test)
ARMNN_AUTO_TEST_CASE(LessOrEqualBroadcast1dVectorFloat16, LessOrEqualBroadcast1dVectorFloat16Test)

ARMNN_AUTO_TEST_CASE(LessOrEqualSimpleUint8,            LessOrEqualSimpleUint8Test)
ARMNN_AUTO_TEST_CASE(LessOrEqualBroadcast1ElementUint8, LessOrEqualBroadcast1ElementUint8Test)
ARMNN_AUTO_TEST_CASE(LessOrEqualBroadcast1dVectorUint8, LessOrEqualBroadcast1dVectorUint8Test)

// NotEqual
ARMNN_AUTO_TEST_CASE(NotEqualSimple,            NotEqualSimpleTest)
ARMNN_AUTO_TEST_CASE(NotEqualBroadcast1Element, NotEqualBroadcast1ElementTest)
ARMNN_AUTO_TEST_CASE(NotEqualBroadcast1dVector, NotEqualBroadcast1dVectorTest)

ARMNN_AUTO_TEST_CASE(NotEqualSimpleFloat16,            NotEqualSimpleFloat16Test)
ARMNN_AUTO_TEST_CASE(NotEqualBroadcast1ElementFloat16, NotEqualBroadcast1ElementFloat16Test)
ARMNN_AUTO_TEST_CASE(NotEqualBroadcast1dVectorFloat16, NotEqualBroadcast1dVectorFloat16Test)

ARMNN_AUTO_TEST_CASE(NotEqualSimpleUint8,            NotEqualSimpleUint8Test)
ARMNN_AUTO_TEST_CASE(NotEqualBroadcast1ElementUint8, NotEqualBroadcast1ElementUint8Test)
ARMNN_AUTO_TEST_CASE(NotEqualBroadcast1dVectorUint8, NotEqualBroadcast1dVectorUint8Test)

// Softmax
ARMNN_AUTO_TEST_CASE(SimpleSoftmaxBeta1, SimpleSoftmaxTest, 1.0f)
ARMNN_AUTO_TEST_CASE(SimpleSoftmaxBeta2, SimpleSoftmaxTest, 2.0f)
ARMNN_AUTO_TEST_CASE(SimpleSoftmaxBeta1Uint8, SimpleSoftmaxUint8Test, 1.0f)
ARMNN_AUTO_TEST_CASE(SimpleSoftmaxBeta2Uint8, SimpleSoftmaxUint8Test, 2.0f)

// LogSoftmax
ARMNN_AUTO_TEST_CASE(LogSoftmaxFloat32_1, LogSoftmaxTest1<DataType::Float32>)

// Space To Batch Nd
ARMNN_AUTO_TEST_CASE(SpaceToBatchNdSimpleFloat32, SpaceToBatchNdSimpleFloat32Test)
ARMNN_AUTO_TEST_CASE(SpaceToBatchNdMultiChannelsFloat32, SpaceToBatchNdMultiChannelsFloat32Test)
ARMNN_AUTO_TEST_CASE(SpaceToBatchNdMultiBlockFloat32, SpaceToBatchNdMultiBlockFloat32Test)
ARMNN_AUTO_TEST_CASE(SpaceToBatchNdPaddingFloat32, SpaceToBatchNdPaddingFloat32Test)

ARMNN_AUTO_TEST_CASE(SpaceToBatchNdSimpleUint8, SpaceToBatchNdSimpleUint8Test)
ARMNN_AUTO_TEST_CASE(SpaceToBatchNdMultiChannelsUint8, SpaceToBatchNdMultiChannelsUint8Test)
ARMNN_AUTO_TEST_CASE(SpaceToBatchNdMultiBlockUint8, SpaceToBatchNdMultiBlockUint8Test)
ARMNN_AUTO_TEST_CASE(SpaceToBatchNdPaddingUint8, SpaceToBatchNdPaddingUint8Test)

ARMNN_AUTO_TEST_CASE(SpaceToBatchNdSimpleNhwcFloat32, SpaceToBatchNdSimpleNhwcFloat32Test)
ARMNN_AUTO_TEST_CASE(SpaceToBatchNdMultiChannelsNhwcFloat32, SpaceToBatchNdMultiChannelsNhwcFloat32Test)
ARMNN_AUTO_TEST_CASE(SpaceToBatchNdMultiBlockNhwcFloat32, SpaceToBatchNdMultiBlockNhwcFloat32Test)
ARMNN_AUTO_TEST_CASE(SpaceToBatchNdPaddingNhwcFloat32, SpaceToBatchNdPaddingNhwcFloat32Test)

ARMNN_AUTO_TEST_CASE(SpaceToBatchNdSimpleNhwcUint8, SpaceToBatchNdSimpleNhwcUint8Test)
ARMNN_AUTO_TEST_CASE(SpaceToBatchNdMultiChannelsNhwcUint8, SpaceToBatchNdMultiChannelsNhwcUint8Test)
ARMNN_AUTO_TEST_CASE(SpaceToBatchNdMultiBlockNhwcUint8, SpaceToBatchNdMultiBlockNhwcUint8Test)
ARMNN_AUTO_TEST_CASE(SpaceToBatchNdPaddingNhwcUint8, SpaceToBatchNdPaddingNhwcUint8Test)

// Space To Depth
ARMNN_AUTO_TEST_CASE(SpaceToDepthNhwcAsymmQ8, SpaceToDepthNhwcAsymmQ8Test)
ARMNN_AUTO_TEST_CASE(SpaceToDepthNchwAsymmQ8, SpaceToDepthNchwAsymmQ8Test)

ARMNN_AUTO_TEST_CASE(SpaceToDepthNhwx1Float32, SpaceToDepthNhwcFloat32Test1)
ARMNN_AUTO_TEST_CASE(SpaceToDepthNchw1Float32, SpaceToDepthNchwFloat32Test1)

ARMNN_AUTO_TEST_CASE(SpaceToDepthNhwc2Float32, SpaceToDepthNhwcFloat32Test2)
ARMNN_AUTO_TEST_CASE(SpaceToDepthNchw2Float32, SpaceToDepthNchwFloat32Test2)

ARMNN_AUTO_TEST_CASE(SpaceToDepthNhwcQSymm16, SpaceToDepthNhwcQSymm16Test)
ARMNN_AUTO_TEST_CASE(SpaceToDepthNchwQSymm16, SpaceToDepthNchwQSymm16Test)

// Stack
ARMNN_AUTO_TEST_CASE(Stack0Axis,           StackAxis0Float32Test)
ARMNN_AUTO_TEST_CASE(StackOutput4DAxis1,   StackOutput4DAxis1Float32Test)
ARMNN_AUTO_TEST_CASE(StackOutput4DAxis2,   StackOutput4DAxis2Float32Test)
ARMNN_AUTO_TEST_CASE(StackOutput4DAxis3,   StackOutput4DAxis3Float32Test)
ARMNN_AUTO_TEST_CASE(StackOutput3DInputs3, StackOutput3DInputs3Float32Test)
ARMNN_AUTO_TEST_CASE(StackOutput5D,        StackOutput5DFloat32Test)
ARMNN_AUTO_TEST_CASE(StackFloat16,         StackFloat16Test)

// Slice
ARMNN_AUTO_TEST_CASE(Slice4dFloat32, Slice4dFloat32Test)
ARMNN_AUTO_TEST_CASE(Slice3dFloat32, Slice3dFloat32Test)
ARMNN_AUTO_TEST_CASE(Slice2dFloat32, Slice2dFloat32Test)
ARMNN_AUTO_TEST_CASE(Slice1dFloat32, Slice1dFloat32Test)
ARMNN_AUTO_TEST_CASE(Slice4dUint8, Slice4dUint8Test)
ARMNN_AUTO_TEST_CASE(Slice3dUint8, Slice3dUint8Test)
ARMNN_AUTO_TEST_CASE(Slice2dUint8, Slice2dUint8Test)
ARMNN_AUTO_TEST_CASE(Slice1dUint8, Slice1dUint8Test)
ARMNN_AUTO_TEST_CASE(Slice4dInt16, Slice4dInt16Test)
ARMNN_AUTO_TEST_CASE(Slice3dInt16, Slice3dInt16Test)
ARMNN_AUTO_TEST_CASE(Slice2dInt16, Slice2dInt16Test)
ARMNN_AUTO_TEST_CASE(Slice1dInt16, Slice1dInt16Test)

// Strided Slice
ARMNN_AUTO_TEST_CASE(StridedSlice4dFloat32, StridedSlice4dFloat32Test)
ARMNN_AUTO_TEST_CASE(StridedSlice4dReverseFloat32, StridedSlice4dReverseFloat32Test)
ARMNN_AUTO_TEST_CASE(StridedSliceSimpleStrideFloat32, StridedSliceSimpleStrideFloat32Test)
ARMNN_AUTO_TEST_CASE(StridedSliceSimpleRangeMaskFloat32, StridedSliceSimpleRangeMaskFloat32Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskFloat32, StridedSliceShrinkAxisMaskFloat32Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskCTSFloat32, StridedSliceShrinkAxisMaskCTSFloat32Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskBitPosition0Dim3Float32,
                     StridedSliceShrinkAxisMaskBitPosition0Dim3Float32Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskBitPosition0Float32, StridedSliceShrinkAxisMaskBitPosition0Float32Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskBitPosition1Float32, StridedSliceShrinkAxisMaskBitPosition1Float32Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskBitPosition2Float32, StridedSliceShrinkAxisMaskBitPosition2Float32Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskBitPosition3Float32, StridedSliceShrinkAxisMaskBitPosition3Float32Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskBitPosition0And1Float32,
                     StridedSliceShrinkAxisMaskBitPosition0And1Float32Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskBitPosition0And2Float32,
                     StridedSliceShrinkAxisMaskBitPosition0And2Float32Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskBitPosition0And3Float32,
                     StridedSliceShrinkAxisMaskBitPosition0And3Float32Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskBitPosition0And1And3Float32,
                     StridedSliceShrinkAxisMaskBitPosition0And1And3Float32Test)
ARMNN_AUTO_TEST_CASE(StridedSlice3dFloat32, StridedSlice3dFloat32Test)
ARMNN_AUTO_TEST_CASE(StridedSlice3dReverseFloat32, StridedSlice3dReverseFloat32Test)
ARMNN_AUTO_TEST_CASE(StridedSlice2dFloat32, StridedSlice2dFloat32Test)
ARMNN_AUTO_TEST_CASE(StridedSlice2dReverseFloat32, StridedSlice2dReverseFloat32Test)

ARMNN_AUTO_TEST_CASE(StridedSlice4dUint8, StridedSlice4dUint8Test)
ARMNN_AUTO_TEST_CASE(StridedSlice4dReverseUint8, StridedSlice4dReverseUint8Test)
ARMNN_AUTO_TEST_CASE(StridedSliceSimpleStrideUint8, StridedSliceSimpleStrideUint8Test)
ARMNN_AUTO_TEST_CASE(StridedSliceSimpleRangeMaskUint8, StridedSliceSimpleRangeMaskUint8Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskUint8, StridedSliceShrinkAxisMaskUint8Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskBitPosition0Dim3Uint8,
                     StridedSliceShrinkAxisMaskBitPosition0Dim3Uint8Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskBitPosition0Uint8, StridedSliceShrinkAxisMaskBitPosition0Uint8Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskBitPosition1Uint8, StridedSliceShrinkAxisMaskBitPosition1Uint8Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskBitPosition2Uint8, StridedSliceShrinkAxisMaskBitPosition2Uint8Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskBitPosition3Uint8, StridedSliceShrinkAxisMaskBitPosition3Uint8Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskBitPosition0And1Uint8,
                     StridedSliceShrinkAxisMaskBitPosition0And1Uint8Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskBitPosition0And2Uint8,
                     StridedSliceShrinkAxisMaskBitPosition0And2Uint8Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskBitPosition0And3Uint8,
                     StridedSliceShrinkAxisMaskBitPosition0And3Uint8Test)
ARMNN_AUTO_TEST_CASE(StridedSliceShrinkAxisMaskBitPosition0And1And3Uint8,
                     StridedSliceShrinkAxisMaskBitPosition0And1And3Uint8Test)
ARMNN_AUTO_TEST_CASE(StridedSlice3dUint8, StridedSlice3dUint8Test)
ARMNN_AUTO_TEST_CASE(StridedSlice3dReverseUint8, StridedSlice3dReverseUint8Test)
ARMNN_AUTO_TEST_CASE(StridedSlice2dUint8, StridedSlice2dUint8Test)
ARMNN_AUTO_TEST_CASE(StridedSlice2dReverseUint8, StridedSlice2dReverseUint8Test)

// Resize Bilinear - NCHW
ARMNN_AUTO_TEST_CASE(SimpleResizeBilinear,
                     SimpleResizeBilinearTest<DataType::Float32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleResizeBilinearInt8,
                     SimpleResizeBilinearTest<DataType::QAsymmS8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleResizeBilinearUint8,
                     SimpleResizeBilinearTest<DataType::QAsymmU8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeBilinearNop,
                     ResizeBilinearNopTest<DataType::Float32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeBilinearNopInt8,
                     ResizeBilinearNopTest<DataType::QAsymmS8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeBilinearNopUint8,
                     ResizeBilinearNopTest<DataType::QAsymmU8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeBilinearSqMin,
                     ResizeBilinearSqMinTest<DataType::Float32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeBilinearSqMinInt8,
                     ResizeBilinearSqMinTest<DataType::QAsymmS8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeBilinearSqMinUint8,
                     ResizeBilinearSqMinTest<DataType::QAsymmU8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeBilinearMin,
                     ResizeBilinearMinTest<DataType::Float32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeBilinearMinInt8,
                     ResizeBilinearMinTest<DataType::QAsymmS8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeBilinearMinUint8,
                     ResizeBilinearMinTest<DataType::QAsymmU8>,
                     DataLayout::NCHW)

ARMNN_AUTO_TEST_CASE(HalfPixelCentersResizeBilinear,
                     HalfPixelCentersResizeBilinearTest<DataType::Float32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(AlignCornersResizeBilinear,
                     AlignCornersResizeBilinearTest<DataType::Float32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(HalfPixelCentersResizeBilinearInt8,
                     HalfPixelCentersResizeBilinearTest<DataType::QAsymmS8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(AlignCornersResizeBilinearInt8,
                     AlignCornersResizeBilinearTest<DataType::QAsymmS8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(HalfPixelCentersResizeBilinearUint8,
                     HalfPixelCentersResizeBilinearTest<DataType::QAsymmU8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(AlignCornersResizeBilinearUint8,
                     AlignCornersResizeBilinearTest<DataType::QAsymmU8>,
                     DataLayout::NCHW)

// Resize Bilinear - NHWC
ARMNN_AUTO_TEST_CASE(ResizeBilinearNopNhwc,
                     ResizeBilinearNopTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeBilinearNopInt8Nhwc,
                     ResizeBilinearNopTest<DataType::QAsymmS8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeBilinearNopUint8Nhwc,
                     ResizeBilinearNopTest<DataType::QAsymmU8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleResizeBilinearNhwc,
                     SimpleResizeBilinearTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleResizeBilinearInt8Nhwc,
                     SimpleResizeBilinearTest<DataType::QAsymmS8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleResizeBilinearUint8Nhwc,
                     SimpleResizeBilinearTest<DataType::QAsymmU8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeBilinearSqMinNhwc,
                     ResizeBilinearSqMinTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeBilinearSqMinInt8Nhwc,
                     ResizeBilinearSqMinTest<DataType::QAsymmS8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeBilinearSqMinUint8Nhwc,
                     ResizeBilinearSqMinTest<DataType::QAsymmU8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeBilinearMinNhwc,
                     ResizeBilinearMinTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeBilinearMinInt8Nhwc,
                     ResizeBilinearMinTest<DataType::QAsymmS8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeBilinearMinUint8Nhwc,
                     ResizeBilinearMinTest<DataType::QAsymmU8>,
                     DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(HalfPixelCentersResizeBilinearNhwc,
                     HalfPixelCentersResizeBilinearTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(AlignCornersResizeBilinearNhwc,
                     AlignCornersResizeBilinearTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(HalfPixelCentersResizeBilinearInt8Nhwc,
                     HalfPixelCentersResizeBilinearTest<DataType::QAsymmS8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(AlignCornersResizeBilinearInt8Nhwc,
                     AlignCornersResizeBilinearTest<DataType::QAsymmS8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(HalfPixelCentersResizeBilinearUint8Nhwc,
                     HalfPixelCentersResizeBilinearTest<DataType::QAsymmU8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(AlignCornersResizeBilinearUint8Nhwc,
                     AlignCornersResizeBilinearTest<DataType::QAsymmU8>,
                     DataLayout::NHWC)

// Resize NearestNeighbor - NCHW
ARMNN_AUTO_TEST_CASE(SimpleResizeNearestNeighbor,
                     SimpleResizeNearestNeighborTest<DataType::Float32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleResizeNearestNeighborInt8,
                     SimpleResizeNearestNeighborTest<DataType::QAsymmS8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleResizeNearestNeighborUint8,
                     SimpleResizeNearestNeighborTest<DataType::QAsymmU8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborNop,
                     ResizeNearestNeighborNopTest<DataType::Float32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborNopInt8,
                     ResizeNearestNeighborNopTest<DataType::QAsymmS8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborNopUint8,
                     ResizeNearestNeighborNopTest<DataType::QAsymmU8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborSqMin,
                     ResizeNearestNeighborSqMinTest<DataType::Float32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborSqMinInt8,
                     ResizeNearestNeighborSqMinTest<DataType::QAsymmS8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborSqMinUint8,
                     ResizeNearestNeighborSqMinTest<DataType::QAsymmU8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMin,
                     ResizeNearestNeighborMinTest<DataType::Float32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMinInt8,
                     ResizeNearestNeighborMinTest<DataType::QAsymmS8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMinUint8,
                     ResizeNearestNeighborMinTest<DataType::QAsymmU8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMag,
                     ResizeNearestNeighborMagTest<DataType::Float32>,
                     DataLayout::NCHW, 0.1f, 50, 0.1f, 50)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMagInt8,
                     ResizeNearestNeighborMagTest<DataType::QAsymmS8>,
                     DataLayout::NCHW, 0.1f, 50, 0.1f, 50)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMagUint8,
                     ResizeNearestNeighborMagTest<DataType::QAsymmU8>,
                     DataLayout::NCHW, 0.1f, 50, 0.1f, 50)

ARMNN_AUTO_TEST_CASE(HalfPixelCentersResizeNearestNeighbour,
                     HalfPixelCentersResizeNearestNeighbourTest<DataType::Float32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(AlignCornersResizeNearestNeighbour,
                     AlignCornersResizeNearestNeighbourTest<DataType::Float32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(HalfPixelCentersResizeNearestNeighbourInt8,
                     HalfPixelCentersResizeNearestNeighbourTest<DataType::QAsymmS8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(AlignCornersResizeNearestNeighbourInt8,
                     AlignCornersResizeNearestNeighbourTest<DataType::QAsymmS8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(HalfPixelCentersResizeNearestNeighbourUint8,
                     HalfPixelCentersResizeNearestNeighbourTest<DataType::QAsymmU8>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(AlignCornersResizeNearestNeighbourUint8,
                     AlignCornersResizeNearestNeighbourTest<DataType::QAsymmU8>,
                     DataLayout::NCHW)

// Resize NearestNeighbor - NHWC
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborNopNhwc,
                     ResizeNearestNeighborNopTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborNopInt8Nhwc,
                     ResizeNearestNeighborNopTest<DataType::QAsymmS8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborNopUint8Nhwc,
                     ResizeNearestNeighborNopTest<DataType::QAsymmU8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleResizeNearestNeighborNhwc,
                     SimpleResizeNearestNeighborTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleResizeNearestNeighborInt8Nhwc,
                     SimpleResizeNearestNeighborTest<DataType::QAsymmS8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleResizeNearestNeighborUint8Nhwc,
                     SimpleResizeNearestNeighborTest<DataType::QAsymmU8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborSqMinNhwc,
                     ResizeNearestNeighborSqMinTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborSqMinInt8Nhwc,
                     ResizeNearestNeighborSqMinTest<DataType::QAsymmS8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborSqMinUint8Nhwc,
                     ResizeNearestNeighborSqMinTest<DataType::QAsymmU8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMinNhwc,
                     ResizeNearestNeighborMinTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMinInt8Nhwc,
                     ResizeNearestNeighborMinTest<DataType::QAsymmS8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMinUint8Nhwc,
                     ResizeNearestNeighborMinTest<DataType::QAsymmU8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMagNhwc,
                     ResizeNearestNeighborMagTest<DataType::Float32>,
                     DataLayout::NHWC, 0.1f, 50, 0.1f, 50)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMagInt8Nhwc,
                     ResizeNearestNeighborMagTest<DataType::QAsymmS8>,
                     DataLayout::NHWC, 0.1f, 50, 0.1f, 50)
ARMNN_AUTO_TEST_CASE(ResizeNearestNeighborMagUint8Nhwc,
                     ResizeNearestNeighborMagTest<DataType::QAsymmU8>,
                     DataLayout::NHWC, 0.1f, 50, 0.1f, 50)

ARMNN_AUTO_TEST_CASE(HalfPixelCentersResizeNearestNeighbourNhwc,
                     HalfPixelCentersResizeNearestNeighbourTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(AlignCornersResizeNearestNeighbourNhwc,
                     AlignCornersResizeNearestNeighbourTest<DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(HalfPixelCentersResizeNearestNeighbourInt8Nhwc,
                     HalfPixelCentersResizeNearestNeighbourTest<DataType::QAsymmS8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(AlignCornersResizeNearestNeighbourInt8Nhwc,
                     AlignCornersResizeNearestNeighbourTest<DataType::QAsymmS8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(HalfPixelCentersResizeNearestNeighbourUint8Nhwc,
                     HalfPixelCentersResizeNearestNeighbourTest<DataType::QAsymmU8>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(AlignCornersResizeNearestNeighbourUint8Nhwc,
                     AlignCornersResizeNearestNeighbourTest<DataType::QAsymmU8>,
                     DataLayout::NHWC)

// Rsqrt
ARMNN_AUTO_TEST_CASE(Rsqrt2d, Rsqrt2dTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(Rsqrt3d, Rsqrt3dTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(RsqrtZero, RsqrtZeroTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(RsqrtNegative, RsqrtNegativeTest<DataType::Float32>)

// Quantize
ARMNN_AUTO_TEST_CASE(QuantizeSimpleUint8, QuantizeSimpleUint8Test)
ARMNN_AUTO_TEST_CASE(QuantizeClampUint8, QuantizeClampUint8Test)

// Dequantize
ARMNN_AUTO_TEST_CASE(DequantizeSimpleUint8, DequantizeSimpleUint8Test)
ARMNN_AUTO_TEST_CASE(DequantizeOffsetUint8, DequantizeOffsetUint8Test)
ARMNN_AUTO_TEST_CASE(DequantizeSimpleInt16, DequantizeSimpleInt16Test)
ARMNN_AUTO_TEST_CASE(DequantizeSimpleUint8ToFp16, DequantizeSimpleUint8ToFp16Test)
ARMNN_AUTO_TEST_CASE(DequantizeSimpleInt16ToFp16, DequantizeSimpleInt16ToFp16Test)

// Transpose
ARMNN_AUTO_TEST_CASE(SimpleTransposeFloat32, SimpleTransposeTest<ClWorkloadFactory, DataType::Float32>)
ARMNN_AUTO_TEST_CASE(TransposeFloat32ValueSet1Test, TransposeValueSet1Test<ClWorkloadFactory, DataType::Float32>)
ARMNN_AUTO_TEST_CASE(TransposeFloat32ValueSet2Test, TransposeValueSet2Test<ClWorkloadFactory, DataType::Float32>)
ARMNN_AUTO_TEST_CASE(TransposeFloat32ValueSet3Test, TransposeValueSet3Test<ClWorkloadFactory, DataType::Float32>)
ARMNN_AUTO_TEST_CASE(SimpleTransposeQASymmS8, SimpleTransposeTest<ClWorkloadFactory, DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(TransposeQASymmS8ValueSet1Test, TransposeValueSet1Test<ClWorkloadFactory, DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(TransposeQASymmS8ValueSet2Test, TransposeValueSet2Test<ClWorkloadFactory, DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(TransposeQASymmS8ValueSet3Test, TransposeValueSet3Test<ClWorkloadFactory, DataType::QAsymmS8>)
ARMNN_AUTO_TEST_CASE(SimpleTransposeQASymm8, SimpleTransposeTest<ClWorkloadFactory, DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(TransposeQASymm8ValueSet1Test, TransposeValueSet1Test<ClWorkloadFactory, DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(TransposeQASymm8ValueSet2Test, TransposeValueSet2Test<ClWorkloadFactory, DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(TransposeQASymm8ValueSet3Test, TransposeValueSet3Test<ClWorkloadFactory, DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(SimpleTransposeQSymm16, SimpleTransposeTest<ClWorkloadFactory, DataType::QSymmS16>)
ARMNN_AUTO_TEST_CASE(TransposeQSymm16ValueSet1Test, TransposeValueSet1Test<ClWorkloadFactory, DataType::QSymmS16>)
ARMNN_AUTO_TEST_CASE(TransposeQSymm16ValueSet2Test, TransposeValueSet2Test<ClWorkloadFactory, DataType::QSymmS16>)
ARMNN_AUTO_TEST_CASE(TransposeQSymm16ValueSet3Test, TransposeValueSet3Test<ClWorkloadFactory, DataType::QSymmS16>)

// TransposeConvolution2d
ARMNN_AUTO_TEST_CASE(SimpleTransposeConvolution2dFloatNchw,
                     SimpleTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     true,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleTransposeConvolution2dFloatNhwc,
                     SimpleTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     true,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(SimpleTransposeConvolution2dUint8Nchw,
                     SimpleTransposeConvolution2dTest<DataType::QAsymmU8, DataType::Signed32>,
                     true,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(SimpleTransposeConvolution2dUint8Nhwc,
                     SimpleTransposeConvolution2dTest<DataType::QAsymmU8, DataType::Signed32>,
                     true,
                     DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(UnbiasedSimpleTransposeConvolution2dFloatNchw,
                     SimpleTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     false,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedSimpleTransposeConvolution2dFloatNhwc,
                     SimpleTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     true,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(UnbiasedSimpleTransposeConvolution2dUint8Nchw,
                     SimpleTransposeConvolution2dTest<DataType::QAsymmU8, DataType::Signed32>,
                     true,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedSimpleTransposeConvolution2dUint8Nhwc,
                     SimpleTransposeConvolution2dTest<DataType::QAsymmU8, DataType::Signed32>,
                     true,
                     DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(PaddedTransposeConvolution2dFloatNchw,
                     PaddedTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     true,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(PaddedTransposeConvolution2dFloatNhwc,
                     PaddedTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     true,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(PaddedTransposeConvolution2dUint8Nchw,
                     PaddedTransposeConvolution2dTest<DataType::QAsymmU8, DataType::Signed32>,
                     true,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(PaddedTransposeConvolution2dUint8Nhwc,
                     PaddedTransposeConvolution2dTest<DataType::QAsymmU8, DataType::Signed32>,
                     true,
                     DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(UnbiasedPaddedTransposeConvolution2dFloatNchw,
                     PaddedTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     false,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedPaddedTransposeConvolution2dFloatNhwc,
                     PaddedTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     true,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(UnbiasedPaddedTransposeConvolution2dUint8Nchw,
                     PaddedTransposeConvolution2dTest<DataType::QAsymmU8, DataType::Signed32>,
                     true,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedPaddedTransposeConvolution2dUint8Nhwc,
                     PaddedTransposeConvolution2dTest<DataType::QAsymmU8, DataType::Signed32>,
                     true,
                     DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(StridedTransposeConvolution2dFloatNchw,
                     StridedTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     true,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(StridedTransposeConvolution2dFloatNhwc,
                     StridedTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     true,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(StridedTransposeConvolution2dUint8Nchw,
                     StridedTransposeConvolution2dTest<DataType::QAsymmU8, DataType::Signed32>,
                     true,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(StridedTransposeConvolution2dUint8Nhwc,
                     StridedTransposeConvolution2dTest<DataType::QAsymmU8, DataType::Signed32>,
                     true,
                     DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(UnbiasedStridedTransposeConvolution2dFloatNchw,
                     StridedTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     false,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedStridedTransposeConvolution2dFloatNhwc,
                     StridedTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     true,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(UnbiasedStridedTransposeConvolution2dUint8Nchw,
                     StridedTransposeConvolution2dTest<DataType::QAsymmU8, DataType::Signed32>,
                     true,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(UnbiasedStridedTransposeConvolution2dUint8Nhwc,
                     StridedTransposeConvolution2dTest<DataType::QAsymmU8, DataType::Signed32>,
                     true,
                     DataLayout::NHWC)

ARMNN_AUTO_TEST_CASE(MultiChannelTransposeConvolution2dFloatNchw,
                     MultiChannelTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(MultiChannelTransposeConvolution2dFloatNhwc,
                     MultiChannelTransposeConvolution2dTest<DataType::Float32, DataType::Float32>,
                     DataLayout::NHWC)
ARMNN_AUTO_TEST_CASE(MultiChannelTransposeConvolution2dUint8Nchw,
                     MultiChannelTransposeConvolution2dTest<DataType::QAsymmU8, DataType::Signed32>,
                     DataLayout::NCHW)
ARMNN_AUTO_TEST_CASE(MultiChannelTransposeConvolution2dUint8Nhwc,
                     MultiChannelTransposeConvolution2dTest<DataType::QAsymmU8, DataType::Signed32>,
                     DataLayout::NHWC)

// Abs
ARMNN_AUTO_TEST_CASE(Abs2d, Abs2dTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(Abs3d, Abs3dTest<DataType::Float32>)

ARMNN_AUTO_TEST_CASE(AbsZero, AbsZeroTest<DataType::Float32>)

ARMNN_AUTO_TEST_CASE(Abs2dFloat16, Abs2dTest<DataType::Float16>)
ARMNN_AUTO_TEST_CASE(Abs3dFloat16, Abs3dTest<DataType::Float16>)

ARMNN_AUTO_TEST_CASE(AbsZeroFloat16, AbsZeroTest<DataType::Float16>)

// ArgMinMax
ARMNN_AUTO_TEST_CASE(ArgMinFloat32, ArgMinSimpleTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(ArgMaxFloat32, ArgMaxSimpleTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(ArgMinChannel, ArgMinChannelTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(ArgMaxChannel, ArgMaxChannelTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(ArgMaxHeight, ArgMaxHeightTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(ArgMinWidth, ArgMinWidthTest<DataType::Float32>)

ARMNN_AUTO_TEST_CASE(ArgMinQAsymm8, ArgMinSimpleTest<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(ArgMaxQAsymm8, ArgMaxSimpleTest<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(ArgMinChannelQAsymm8, ArgMinChannelTest<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(ArgMaxChannelQAsymm8, ArgMaxChannelTest<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(ArgMaxHeightQAsymm8, ArgMaxHeightTest<DataType::QAsymmU8>)
ARMNN_AUTO_TEST_CASE(ArgMinWidthQAsymm8, ArgMinWidthTest<DataType::QAsymmU8>)

// Neg
ARMNN_AUTO_TEST_CASE(Neg2d, Neg2dTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(Neg3d, Neg3dTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(NegZero, NegZeroTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(NegNegative, NegNegativeTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(Neg2dFloat16, Neg2dTest<DataType::Float16>)
ARMNN_AUTO_TEST_CASE(Neg3dFloat16, Neg3dTest<DataType::Float16>)

// Exp
ARMNN_AUTO_TEST_CASE(Exp2d, Exp2dTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(Exo3d, Exp3dTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(ExpZero, ExpZeroTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(ExpNegative, ExpNegativeTest<DataType::Float32>)
ARMNN_AUTO_TEST_CASE(Exp2dFloat16, Exp2dTest<DataType::Float16>)
ARMNN_AUTO_TEST_CASE(Exp3dFloat16, Exp3dTest<DataType::Float16>)

#if defined(ARMNNREF_ENABLED)

// The ARMNN_COMPARE_REF_AUTO_TEST_CASE and the ARMNN_COMPARE_REF_FIXTURE_TEST_CASE test units are not available
// if the reference backend is not built

// ============================================================================
// COMPARE tests

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareSoftmaxBeta1WithReference, CompareSoftmaxTest, 1.0f)
ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareSoftmaxBeta2WithReference, CompareSoftmaxTest, 2.0f)
ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareSoftmaxUint8, CompareSoftmaxUint8Test, 1.0f)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareConv2dWithReference, CompareConvolution2dTest)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareDepthwiseConv2dWithReferenceFloat32,
                                 CompareDepthwiseConvolution2dFloatTest,
                                 DataLayout::NCHW)
ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareDepthwiseConv2dWithReferenceUint8,
                                 CompareDepthwiseConvolution2dUint8Test,
                                 DataLayout::NCHW)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareDepthwiseConv2dWithReferenceFloat32Nhwc,
                                 CompareDepthwiseConvolution2dFloatTest,
                                 DataLayout::NHWC)
ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareDepthwiseConv2dWithReferenceUint8Nhwc,
                                 CompareDepthwiseConvolution2dUint8Test,
                                 DataLayout::NHWC)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareNormalizationWithinWithReference, CompareNormalizationTest,
                                 NormalizationAlgorithmChannel::Within,
                                 NormalizationAlgorithmMethod::LocalBrightness)
ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareNormalizationAcrossWithReference, CompareNormalizationTest,
                                 NormalizationAlgorithmChannel::Across,
                                 NormalizationAlgorithmMethod::LocalBrightness)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareMaxPooling2dWithRef, ComparePooling2dTest, PoolingAlgorithm::Max)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareAveragePooling2dWithRef, ComparePooling2dTest, PoolingAlgorithm::Average)
ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareAveragePooling2dWithRefUint8, ComparePooling2dUint8Test,
                                 PoolingAlgorithm::Average)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareL2Pooling2dWithRef, ComparePooling2dTest, PoolingAlgorithm::L2)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareAddition, CompareAdditionTest)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareMultiplicationWithRef, CompareMultiplicationTest)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareBatchNorm, CompareBatchNormTest)

ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareReLu1, CompareBoundedReLuTest, 1.0f, -1.0f)
ARMNN_COMPARE_REF_AUTO_TEST_CASE(CompareReLu6, CompareBoundedReLuTest, 6.0f, 0.0f)

// ============================================================================
// FIXTURE tests

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareSigmoidActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::Sigmoid, 5u)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareTanhActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::TanH, 5u)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareLinearActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::Linear, 5u)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareReLuActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::ReLu, 5u)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareBoundedReLuActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::BoundedReLu, 5u)
ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareBoundedReLuActivationWithReferenceUint8, ActivationFixture,
                                    CompareActivationUint8Test, ActivationFunction::BoundedReLu)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareSoftReLuActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::SoftReLu, 5u)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareLeakyReLuActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::LeakyReLu, 5u)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareAbsActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::Abs, 5u)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareSqrtActivationWithReference, PositiveActivationFixture,
                                    CompareActivationTest, ActivationFunction::Sqrt, 5u)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareSquareActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::Square, 5u)

ARMNN_COMPARE_REF_FIXTURE_TEST_CASE(CompareEluActivationWithReference, ActivationFixture,
                                    CompareActivationTest, ActivationFunction::Elu, 5u)

#endif

BOOST_AUTO_TEST_SUITE_END()

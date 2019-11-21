//
// Created by daquexian on 2019/8/6.
//
// This file is mostly generated by generate_code.py based on ops.yml
#include <common/data_types.h>
#include <common/helper.h>
#include <dnnlibrary/ModelBuilder.h>
#include <dnnlibrary/nnapi_helper.h>

namespace dnn {
using namespace android::nn::wrapper;

// ModelBuilder auto generated methods start
expected<Unit, std::string> ModelBuilder::AddLayer_CONV_2D(
    const std::string &input, const std::string &weight,
    const dnn::optional<std::string> &bias, int32_t padding_left,
    int32_t padding_right, int32_t padding_top, int32_t padding_bottom,
    int32_t stride_x, int32_t stride_y, int32_t fuse_code,
    const std::string &output,
    const dnn::optional<QuantInfo> &output_quant_info) {
    if (nnapi_->android_sdk_version < 27) {
        return make_unexpected("CONV_2D requires API 27");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    imm_blob_inputs_.insert(weight);
    const auto weight_idx = operand_indexes_.at(weight);
    input_indexes.push_back(weight_idx);
    uint32_t bias_idx_val;
    css bias_val = bias.value_or(weight + "_b");
    if (!bias.has_value()) {
        const auto weight_dimen = shaper_[weight];
        const Shape bias_dimen{weight_dimen[0]};
        const auto &weight_type = operand_types_.at(weight).type;
        if (weight_type == Type::TENSOR_FLOAT32) {
            bias_idx_val =
                FillOperand(bias_val, {Type::TENSOR_FLOAT32, bias_dimen}, 0.f);
        } else if (weight_type == Type::TENSOR_QUANT8_ASYMM) {
            const auto input_scale = operand_types_.at(input).operandType.scale;
            const auto weight_scale =
                operand_types_.at(weight).operandType.scale;
            bias_idx_val = FillOperand(
                bias_val,
                {Type::TENSOR_INT32, bias_dimen, input_scale * weight_scale},
                0);
        } else {
            return make_unexpected("Unknown type " + typeToStr(weight_type));
        }
    } else {
        bias_idx_val = operand_indexes_.at(bias.value());
    }
    input_indexes.push_back(bias_idx_val);
    AddScalarOperands(input_indexes, padding_left, padding_right, padding_top,
                      padding_bottom, stride_x, stride_y, fuse_code);
    shaper_.Conv(input, weight, padding_left, padding_right, padding_top,
                 padding_bottom, stride_x, stride_y, output);
    const OperandType operand_type = GetOperandType(
        operand_types_.at(input).type, shaper_[output], output_quant_info);
    const auto output_idx =
        AddOperation(ANEURALNETWORKS_CONV_2D, input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_AVERAGE_POOL_2D(
    const std::string &input, int32_t padding_left, int32_t padding_right,
    int32_t padding_top, int32_t padding_bottom, int32_t stride_x,
    int32_t stride_y, int32_t kernel_width, int32_t kernel_height,
    int32_t fuse_code, const std::string &output,
    const dnn::optional<QuantInfo> &output_quant_info) {
    if (nnapi_->android_sdk_version < 27) {
        return make_unexpected("AVERAGE_POOL_2D requires API 27");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    AddScalarOperands(input_indexes, padding_left, padding_right, padding_top,
                      padding_bottom, stride_x, stride_y, kernel_width,
                      kernel_height, fuse_code);
    shaper_.Pool(input, padding_left, padding_right, padding_top,
                 padding_bottom, stride_x, stride_y, kernel_width,
                 kernel_height, output);
    const OperandType operand_type = GetOperandType(
        operand_types_.at(input).type, shaper_[output], output_quant_info);
    const auto output_idx = AddOperation(ANEURALNETWORKS_AVERAGE_POOL_2D,
                                         input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_MAX_POOL_2D(
    const std::string &input, int32_t padding_left, int32_t padding_right,
    int32_t padding_top, int32_t padding_bottom, int32_t stride_x,
    int32_t stride_y, int32_t kernel_width, int32_t kernel_height,
    int32_t fuse_code, const std::string &output,
    const dnn::optional<QuantInfo> &output_quant_info) {
    if (nnapi_->android_sdk_version < 27) {
        return make_unexpected("MAX_POOL_2D requires API 27");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    AddScalarOperands(input_indexes, padding_left, padding_right, padding_top,
                      padding_bottom, stride_x, stride_y, kernel_width,
                      kernel_height, fuse_code);
    shaper_.Pool(input, padding_left, padding_right, padding_top,
                 padding_bottom, stride_x, stride_y, kernel_width,
                 kernel_height, output);
    const OperandType operand_type = GetOperandType(
        operand_types_.at(input).type, shaper_[output], output_quant_info);
    const auto output_idx = AddOperation(ANEURALNETWORKS_MAX_POOL_2D,
                                         input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_RELU(
    const std::string &input, const std::string &output) {
    if (nnapi_->android_sdk_version < 27) {
        return make_unexpected("RELU requires API 27");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    shaper_.Identity(input, output);
    const OperandType operand_type =
        GetOperandType(operand_types_.at(input).type, shaper_[output]);
    const auto output_idx =
        AddOperation(ANEURALNETWORKS_RELU, input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_SOFTMAX(
    const std::string &input, float beta, const std::string &output) {
    if (nnapi_->android_sdk_version < 27) {
        return make_unexpected("SOFTMAX requires API 27");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    AddScalarOperands(input_indexes, beta);
    shaper_.Identity(input, output);
    const OperandType operand_type =
        GetOperandType(operand_types_.at(input).type, shaper_[output]);
    const auto output_idx =
        AddOperation(ANEURALNETWORKS_SOFTMAX, input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_FULLY_CONNECTED(
    const std::string &input, const std::string &weight,
    const dnn::optional<std::string> &bias, int32_t fuse_code,
    const std::string &output,
    const dnn::optional<QuantInfo> &output_quant_info) {
    if (nnapi_->android_sdk_version < 27) {
        return make_unexpected("FULLY_CONNECTED requires API 27");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    imm_blob_inputs_.insert(weight);
    const auto weight_idx = operand_indexes_.at(weight);
    input_indexes.push_back(weight_idx);
    uint32_t bias_idx_val;
    css bias_val = bias.value_or(weight + "_b");
    if (!bias.has_value()) {
        const auto weight_dimen = shaper_[weight];
        const Shape bias_dimen{weight_dimen[0]};
        const auto &weight_type = operand_types_.at(weight).type;
        if (weight_type == Type::TENSOR_FLOAT32) {
            bias_idx_val =
                FillOperand(bias_val, {Type::TENSOR_FLOAT32, bias_dimen}, 0.f);
        } else if (weight_type == Type::TENSOR_QUANT8_ASYMM) {
            const auto input_scale = operand_types_.at(input).operandType.scale;
            const auto weight_scale =
                operand_types_.at(weight).operandType.scale;
            bias_idx_val = FillOperand(
                bias_val,
                {Type::TENSOR_INT32, bias_dimen, input_scale * weight_scale},
                0);
        } else {
            return make_unexpected("Unknown type " + typeToStr(weight_type));
        }
    } else {
        bias_idx_val = operand_indexes_.at(bias.value());
    }
    input_indexes.push_back(bias_idx_val);
    AddScalarOperands(input_indexes, fuse_code);
    shaper_.FC(input, weight, output);
    const OperandType operand_type = GetOperandType(
        operand_types_.at(input).type, shaper_[output], output_quant_info);
    const auto output_idx = AddOperation(ANEURALNETWORKS_FULLY_CONNECTED,
                                         input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_ADD(
    const std::string &input1, const std::string &input2, int32_t fuse_code,
    const std::string &output,
    const dnn::optional<QuantInfo> &output_quant_info) {
    if (nnapi_->android_sdk_version < 27) {
        return make_unexpected("ADD requires API 27");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input1);
    const auto input1_idx = operand_indexes_.at(input1);
    input_indexes.push_back(input1_idx);
    imm_blob_inputs_.insert(input2);
    const auto input2_idx = operand_indexes_.at(input2);
    input_indexes.push_back(input2_idx);
    AddScalarOperands(input_indexes, fuse_code);
    shaper_.Eltwise(input1, input2, output);
    const OperandType operand_type = GetOperandType(
        operand_types_.at(input1).type, shaper_[output], output_quant_info);
    const auto output_idx =
        AddOperation(ANEURALNETWORKS_ADD, input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_CONCATENATION(
    const std::vector<std::string> &inputs, int32_t axis,
    const std::string &output) {
    if (nnapi_->android_sdk_version < 27) {
        return make_unexpected("CONCATENATION requires API 27");
    }
    IndexSeq input_indexes;
    for (const auto &x : inputs) {
        imm_blob_inputs_.insert(x);
        input_indexes.push_back(operand_indexes_.at(x));
    }
    AddScalarOperands(input_indexes, axis);
    shaper_.Concat(inputs, axis, output);
    const OperandType operand_type =
        GetOperandType(operand_types_.at(inputs[0]).type, shaper_[output]);
    const auto output_idx = AddOperation(ANEURALNETWORKS_CONCATENATION,
                                         input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_DEPTHWISE_CONV_2D(
    const std::string &input, const std::string &weight,
    const dnn::optional<std::string> &bias, int32_t padding_left,
    int32_t padding_right, int32_t padding_top, int32_t padding_bottom,
    int32_t stride_x, int32_t stride_y, int32_t depth_multiplier,
    int32_t fuse_code, const std::string &output,
    const dnn::optional<QuantInfo> &output_quant_info) {
    if (nnapi_->android_sdk_version < 27) {
        return make_unexpected("DEPTHWISE_CONV_2D requires API 27");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    imm_blob_inputs_.insert(weight);
    const auto weight_idx = operand_indexes_.at(weight);
    input_indexes.push_back(weight_idx);
    uint32_t bias_idx_val;
    css bias_val = bias.value_or(weight + "_b");
    if (!bias.has_value()) {
        const auto weight_dimen = shaper_[weight];
        const Shape bias_dimen{weight_dimen[0]};
        const auto &weight_type = operand_types_.at(weight).type;
        if (weight_type == Type::TENSOR_FLOAT32) {
            bias_idx_val =
                FillOperand(bias_val, {Type::TENSOR_FLOAT32, bias_dimen}, 0.f);
        } else if (weight_type == Type::TENSOR_QUANT8_ASYMM) {
            const auto input_scale = operand_types_.at(input).operandType.scale;
            const auto weight_scale =
                operand_types_.at(weight).operandType.scale;
            bias_idx_val = FillOperand(
                bias_val,
                {Type::TENSOR_INT32, bias_dimen, input_scale * weight_scale},
                0);
        } else {
            return make_unexpected("Unknown type " + typeToStr(weight_type));
        }
    } else {
        bias_idx_val = operand_indexes_.at(bias.value());
    }
    input_indexes.push_back(bias_idx_val);
    AddScalarOperands(input_indexes, padding_left, padding_right, padding_top,
                      padding_bottom, stride_x, stride_y, depth_multiplier,
                      fuse_code);
    shaper_.DepthwiseConv(input, weight, padding_left, padding_right,
                          padding_top, padding_bottom, stride_x, stride_y,
                          output);
    const OperandType operand_type = GetOperandType(
        operand_types_.at(input).type, shaper_[output], output_quant_info);
    const auto output_idx = AddOperation(ANEURALNETWORKS_DEPTHWISE_CONV_2D,
                                         input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_BATCH_TO_SPACE_ND(
    const std::string &input, const std::vector<int32_t> &block_sizes,
    const std::string &output) {
    if (nnapi_->android_sdk_version < 28) {
        return make_unexpected("BATCH_TO_SPACE_ND requires API 28");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    const auto block_sizes_idx = AddTensorFromBuffer(
        "input_block_sizes_of_" + output, &block_sizes[0],
        {Type::TENSOR_INT32, Shape{static_cast<uint32_t>(block_sizes.size())}});
    input_indexes.push_back(block_sizes_idx);
    shaper_.BatchToSpace(input, block_sizes, output);
    const OperandType operand_type =
        GetOperandType(operand_types_.at(input).type, shaper_[output]);
    const auto output_idx = AddOperation(ANEURALNETWORKS_BATCH_TO_SPACE_ND,
                                         input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_SPACE_TO_BATCH_ND(
    const std::string &input, const std::vector<int32_t> &block_sizes,
    const std::vector<int32_t> &pads, const std::string &output) {
    if (nnapi_->android_sdk_version < 28) {
        return make_unexpected("SPACE_TO_BATCH_ND requires API 28");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    const auto block_sizes_idx = AddTensorFromBuffer(
        "input_block_sizes_of_" + output, &block_sizes[0],
        {Type::TENSOR_INT32, Shape{static_cast<uint32_t>(block_sizes.size())}});
    input_indexes.push_back(block_sizes_idx);
    const auto pads_idx = AddTensorFromBuffer(
        "input_pads_of_" + output, &pads[0],
        {Type::TENSOR_INT32, Shape{static_cast<uint32_t>(pads.size())}});
    input_indexes.push_back(pads_idx);
    shaper_.SpaceToBatch(input, block_sizes, pads, output);
    const OperandType operand_type =
        GetOperandType(operand_types_.at(input).type, shaper_[output]);
    const auto output_idx = AddOperation(ANEURALNETWORKS_SPACE_TO_BATCH_ND,
                                         input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_STRIDED_SLICE(
    const std::string &input, const std::vector<int32_t> &starts,
    const std::vector<int32_t> &ends, const std::vector<int32_t> &strides,
    int32_t begin_mask, int32_t end_mask, int32_t shrink_axis_mask,
    const std::string &output) {
    if (nnapi_->android_sdk_version < 28) {
        return make_unexpected("STRIDED_SLICE requires API 28");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    const auto starts_idx = AddTensorFromBuffer(
        "input_starts_of_" + output, &starts[0],
        {Type::TENSOR_INT32, Shape{static_cast<uint32_t>(starts.size())}});
    input_indexes.push_back(starts_idx);
    const auto ends_idx = AddTensorFromBuffer(
        "input_ends_of_" + output, &ends[0],
        {Type::TENSOR_INT32, Shape{static_cast<uint32_t>(ends.size())}});
    input_indexes.push_back(ends_idx);
    const auto strides_idx = AddTensorFromBuffer(
        "input_strides_of_" + output, &strides[0],
        {Type::TENSOR_INT32, Shape{static_cast<uint32_t>(strides.size())}});
    input_indexes.push_back(strides_idx);
    AddScalarOperands(input_indexes, begin_mask, end_mask, shrink_axis_mask);
    shaper_.StridedSlice(input, starts, ends, strides, begin_mask, end_mask,
                         shrink_axis_mask, output);
    const OperandType operand_type =
        GetOperandType(operand_types_.at(input).type, shaper_[output]);
    const auto output_idx = AddOperation(ANEURALNETWORKS_STRIDED_SLICE,
                                         input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_MUL(
    const std::string &input1, const std::string &input2, int32_t fuse_code,
    const std::string &output,
    const dnn::optional<QuantInfo> &output_quant_info) {
    if (nnapi_->android_sdk_version < 27) {
        return make_unexpected("MUL requires API 27");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input1);
    const auto input1_idx = operand_indexes_.at(input1);
    input_indexes.push_back(input1_idx);
    imm_blob_inputs_.insert(input2);
    const auto input2_idx = operand_indexes_.at(input2);
    input_indexes.push_back(input2_idx);
    AddScalarOperands(input_indexes, fuse_code);
    shaper_.Eltwise(input1, input2, output);
    const OperandType operand_type = GetOperandType(
        operand_types_.at(input1).type, shaper_[output], output_quant_info);
    const auto output_idx =
        AddOperation(ANEURALNETWORKS_MUL, input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_DEQUANTIZE(
    const std::string &input, const std::string &output) {
    if (nnapi_->android_sdk_version < 27) {
        return make_unexpected("DEQUANTIZE requires API 27");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    shaper_.Identity(input, output);
    const OperandType operand_type =
        GetOperandType(Type::FLOAT32, shaper_[output]);
    const auto output_idx = AddOperation(ANEURALNETWORKS_DEQUANTIZE,
                                         input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_LOCAL_RESPONSE_NORMALIZATION(
    const std::string &input, int32_t radius, float bias, float alpha,
    float beta, const std::string &output) {
    if (nnapi_->android_sdk_version < 27) {
        return make_unexpected("LOCAL_RESPONSE_NORMALIZATION requires API 27");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    AddScalarOperands(input_indexes, radius, bias, alpha, beta);
    shaper_.Identity(input, output);
    const OperandType operand_type =
        GetOperandType(operand_types_.at(input).type, shaper_[output]);
    const auto output_idx =
        AddOperation(ANEURALNETWORKS_LOCAL_RESPONSE_NORMALIZATION,
                     input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_TANH(
    const std::string &input, const std::string &output) {
    if (nnapi_->android_sdk_version < 27) {
        return make_unexpected("TANH requires API 27");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    shaper_.Identity(input, output);
    const OperandType operand_type =
        GetOperandType(operand_types_.at(input).type, shaper_[output]);
    const auto output_idx =
        AddOperation(ANEURALNETWORKS_TANH, input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_FLOOR(
    const std::string &input, const std::string &output) {
    if (nnapi_->android_sdk_version < 27) {
        return make_unexpected("FLOOR requires API 27");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    shaper_.Identity(input, output);
    const OperandType operand_type =
        GetOperandType(operand_types_.at(input).type, shaper_[output]);
    const auto output_idx =
        AddOperation(ANEURALNETWORKS_FLOOR, input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_LOGISTIC(
    const std::string &input, const std::string &output) {
    if (nnapi_->android_sdk_version < 27) {
        return make_unexpected("LOGISTIC requires API 27");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    shaper_.Identity(input, output);
    const OperandType operand_type =
        GetOperandType(operand_types_.at(input).type, shaper_[output]);
    const auto output_idx =
        AddOperation(ANEURALNETWORKS_LOGISTIC, input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_PRELU_Impl(
    const std::string &input, const std::string &alpha,
    const std::string &output) {
    if (nnapi_->android_sdk_version < 29) {
        return make_unexpected("PRELU requires API 29");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    imm_blob_inputs_.insert(alpha);
    const auto alpha_idx = operand_indexes_.at(alpha);
    input_indexes.push_back(alpha_idx);
    shaper_.Identity(input, output);
    const OperandType operand_type =
        GetOperandType(operand_types_.at(input).type, shaper_[output]);
    const auto output_idx =
        AddOperation(ANEURALNETWORKS_PRELU, input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_POW(
    const std::string &input, const std::string &exp,
    const std::string &output) {
    if (nnapi_->android_sdk_version < 29) {
        return make_unexpected("POW requires API 29");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    imm_blob_inputs_.insert(exp);
    const auto exp_idx = operand_indexes_.at(exp);
    input_indexes.push_back(exp_idx);
    shaper_.Identity(input, output);
    const OperandType operand_type =
        GetOperandType(operand_types_.at(input).type, shaper_[output]);
    const auto output_idx =
        AddOperation(ANEURALNETWORKS_POW, input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_NEG(
    const std::string &input, const std::string &output) {
    if (nnapi_->android_sdk_version < 29) {
        return make_unexpected("NEG requires API 29");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    shaper_.Identity(input, output);
    const OperandType operand_type =
        GetOperandType(operand_types_.at(input).type, shaper_[output]);
    const auto output_idx =
        AddOperation(ANEURALNETWORKS_NEG, input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_MINIMUM(
    const std::string &input1, const std::string &input2,
    const std::string &output) {
    if (nnapi_->android_sdk_version < 29) {
        return make_unexpected("MINIMUM requires API 29");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input1);
    const auto input1_idx = operand_indexes_.at(input1);
    input_indexes.push_back(input1_idx);
    imm_blob_inputs_.insert(input2);
    const auto input2_idx = operand_indexes_.at(input2);
    input_indexes.push_back(input2_idx);
    shaper_.Eltwise(input1, input2, output);
    const OperandType operand_type =
        GetOperandType(operand_types_.at(input1).type, shaper_[output]);
    const auto output_idx =
        AddOperation(ANEURALNETWORKS_MINIMUM, input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_MAXIMUM(
    const std::string &input1, const std::string &input2,
    const std::string &output) {
    if (nnapi_->android_sdk_version < 29) {
        return make_unexpected("MAXIMUM requires API 29");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input1);
    const auto input1_idx = operand_indexes_.at(input1);
    input_indexes.push_back(input1_idx);
    imm_blob_inputs_.insert(input2);
    const auto input2_idx = operand_indexes_.at(input2);
    input_indexes.push_back(input2_idx);
    shaper_.Eltwise(input1, input2, output);
    const OperandType operand_type =
        GetOperandType(operand_types_.at(input1).type, shaper_[output]);
    const auto output_idx =
        AddOperation(ANEURALNETWORKS_MAXIMUM, input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

expected<Unit, std::string> ModelBuilder::AddLayer_LOG(
    const std::string &input, const std::string &output) {
    if (nnapi_->android_sdk_version < 29) {
        return make_unexpected("LOG requires API 29");
    }
    IndexSeq input_indexes;
    imm_blob_inputs_.insert(input);
    const auto input_idx = operand_indexes_.at(input);
    input_indexes.push_back(input_idx);
    shaper_.Identity(input, output);
    const OperandType operand_type =
        GetOperandType(operand_types_.at(input).type, shaper_[output]);
    const auto output_idx =
        AddOperation(ANEURALNETWORKS_LOG, input_indexes, operand_type)[0];
    RegisterOperand(output, output_idx, operand_type);
    imm_blob_outputs_.insert(output);
    return Unit();
}

// ModelBuilder auto generated methods end

expected<Unit, std::string> ModelBuilder::AddLayer_PRELU(
    const std::string &input, const std::string &alpha,
    const std::string &output) {
    if (nnapi_->android_sdk_version < 29) {
        const auto neg1_name = output + "_neg1";
        const auto imm1_name = output + "_imm1";
        const auto imm2_name = output + "_imm2";
        const auto imm3_name = output + "_imm3";
        const auto imm4_name = output + "_imm4";
        const auto imm5_name = output + "_imm5";
        // It is supposed to be in onnx converter
        // if (onnx_tensors_[alpha].shape != Shape{1}) {
        //     // TODO: support it
        //     throw std::invalid_argument("Only support one element slope.");
        // }
        // positive branch
        AddLayer_RELU(input, imm1_name);
        // negative branch
        float neg1_buf[1]{-1.f};
        AddTensorFromBuffer(neg1_name, neg1_buf, {Type::TENSOR_FLOAT32, {1}});
        AddLayer_MUL(input, neg1_name, ModelBuilder::ACTIVATION_NONE, imm2_name,
                     dnn::nullopt);
        AddLayer_RELU(imm2_name, imm3_name);
        AddLayer_MUL(imm3_name, alpha, ModelBuilder::ACTIVATION_NONE, imm4_name,
                     dnn::nullopt);
        AddLayer_MUL(imm4_name, neg1_name, ModelBuilder::ACTIVATION_NONE,
                     imm5_name, dnn::nullopt);
        // add two branches
        AddLayer_ADD(imm1_name, imm5_name, ModelBuilder::ACTIVATION_NONE,
                     output, dnn::nullopt);
    } else {
        AddLayer_PRELU_Impl(input, alpha, output);
    }
    return Unit();
}

// Methods for backward compatibility
ModelBuilder::Index ModelBuilder::AddInput(const std::string name,
                                           const uint32_t batch,
                                           const uint32_t height,
                                           const uint32_t width,
                                           const uint32_t depth) {
    const std::vector<uint32_t> dimen{batch, height, width, depth};
    return AddInput(name, {Type::TENSOR_FLOAT32, dimen});
}

ModelBuilder::Index ModelBuilder::AddInput(std::string name,
                                           const OperandType &operand_type) {
    const auto index = AddNewOperand(operand_type);

    shaper_.AddShape(name, operand_type.dimensions);
    input_index_vec_.push_back(index);
    dnn_model_->AddInput(name, shaper_[name]);
    RegisterOperand(name, index, operand_type);
    return index;
}

// ModelBuilder::Index ModelBuilder::AddDepthWiseConv(
//     const std::string &input_name, int32_t strideX, int32_t strideY,
//     int32_t paddingLeft, int32_t paddingRight, int32_t paddingBottom,
//     int32_t paddingTop, int32_t activation, int32_t depthMultiplier,
//     const std::string &weight_name, const dnn::optional<std::string>
//     &bias_name, const std::string &output_name, const
//     dnn::optional<QuantInfo> &output_quant_info) { return
//     AddDepthwiseConv(input_name, weight_name, bias_name, paddingLeft,
//                             paddingRight, paddingTop, paddingBottom, strideX,
//                             strideY, depthMultiplier, activation,
//                             output_name, output_quant_info);
// }
//
// ModelBuilder::Index ModelBuilder::AddConv(
//     const std::string &input_name, const std::string &weight_name,
//     const dnn::optional<std::string> &bias_name,
//     const std::vector<int32_t> paddings, const std::vector<int32_t> strides,
//     int32_t fuse_code, const std::string &output_name,
//     const dnn::optional<QuantInfo> &output_quant_info) {
//     return AddConv(input_name, weight_name, bias_name, paddings[0],
//     paddings[0],
//                    paddings[0], paddings[0], strides[0], strides[1],
//                    fuse_code, output_name, output_quant_info);
// }
//
// ModelBuilder::Index ModelBuilder::AddConv(
//     const std::string &input_name, int32_t strideX, int32_t strideY,
//     int32_t paddingLeft, int32_t paddingRight, int32_t paddingTop,
//     int32_t paddingBottom, int32_t activation, const std::string
//     &weight_name, const dnn::optional<std::string> &bias_name, const
//     std::string &output_name, const dnn::optional<QuantInfo>
//     &output_quant_info) { return AddConv(input_name, weight_name, bias_name,
//     paddingLeft,
//                    paddingRight, paddingTop, paddingBottom, strideX, strideY,
//                    activation, output_name, output_quant_info);
// }
//
// ModelBuilder::Index ModelBuilder::AddPool(
//     const std::string &input_name, int32_t strideX, int32_t strideY,
//     int32_t paddingLeft, int32_t paddingRight, int32_t paddingTop,
//     int32_t paddingBottom, int32_t height, int32_t width, int32_t activation,
//     PoolingType poolingType, const std::string &output_name,
//     const dnn::optional<QuantInfo> &output_quant_info) {
//     if (height == -1 && width == -1) {
//         VLOG(5) << "Global pool, input: " << input_name;
//         const auto inputDimen = shaper_[input_name];
//         height = inputDimen[1];
//         width = inputDimen[2];
//         strideX = width;
//         strideY = height;
//     }
//     switch (poolingType) {
//         case PoolingType::AVE_POOL:
//             return AddAvePool(input_name, paddingLeft, paddingRight,
//             paddingTop,
//                               paddingBottom, strideX, strideY, width, height,
//                               activation, output_name, output_quant_info);
//             break;
//         case PoolingType::MAX_POOL:
//             return AddMaxPool(input_name, paddingLeft, paddingRight,
//             paddingTop,
//                               paddingBottom, strideX, strideY, width, height,
//                               activation, output_name, output_quant_info);
//             break;
//     }
// }
//
// ModelBuilder::Index ModelBuilder::AddFC(
//     const std::string &input_name, int32_t activation,
//     const std::string &weight_name, const dnn::optional<std::string>
//     &bias_name, const std::string &output_name, const
//     dnn::optional<QuantInfo> &output_quant_info) { return AddFC(input_name,
//     weight_name, bias_name, activation, output_name,
//                  output_quant_info);
// }
//
// ModelBuilder::Index ModelBuilder::AddOperationAdd(const std::string
// &input_name,
//                                                   float scalar,
//                                                   std::string output_name) {
//     return AddAdd(input_name, scalar, ANEURALNETWORKS_FUSED_NONE,
//     output_name);
// }
//
// ModelBuilder::Index ModelBuilder::AddOperationAdd(
//     const std::string &input1_name, const std::string &input2_name,
//     const std::string &output_name,
//     const dnn::optional<QuantInfo> &output_quant_info) {
//     return AddAdd(input1_name, input2_name, ANEURALNETWORKS_FUSED_NONE,
//                   output_name, output_quant_info);
// }
//
// ModelBuilder::Index ModelBuilder::AddMul(const std::string &input_name,
//                                          float scalar,
//                                          const std::string &output_name) {
//     return AddMul(input_name, scalar, ANEURALNETWORKS_FUSED_NONE,
//     output_name);
// }
//
// ModelBuilder::Index ModelBuilder::AddMul(
//     const std::string &input1_name, const std::string &input2_name,
//     const std::string &output_name,
//     const dnn::optional<QuantInfo> &output_quant_info) {
//     return AddMul(input1_name, input2_name, ANEURALNETWORKS_FUSED_NONE,
//                   output_name, output_quant_info);
// }
//
template <typename... OperandTypes>
ModelBuilder::IndexSeq ModelBuilder::AddOperation(
    int op, IndexSeq input_indexes, OperandTypes... operand_types) {
    using android::nn::wrapper::OperandType;
    std::vector<OperandType> types;
    (types.push_back(operand_types), ...);
    IndexSeq output_indexes;
    for (const auto &type : types) {
        auto index = AddNewOperand(type);
        output_indexes.push_back(index);
    }

    THROW_ON_ERROR_WITH_NOTE(
        nnapi_->ANeuralNetworksModel_addOperation(
            dnn_model_->model_, op, input_indexes.size(), &input_indexes[0],
            output_indexes.size(), &output_indexes[0]),
        "op = " + std::to_string(op));

    return output_indexes;
}

}  // namespace dnn

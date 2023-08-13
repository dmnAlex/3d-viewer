#ifndef MODEL_FACADE_OPERATION_RESULT_H
#define MODEL_FACADE_OPERATION_RESULT_H

#include <string>

namespace s21 {
class FacadeOperationResult {
 public:
  FacadeOperationResult(std::string message = "", bool is_success = true)
      : error_message_(message), is_success_(is_success) {}

  const std::string& GetErrorMessage() const { return error_message_; }
  void SetErrorMessage(std::string message) { error_message_ = message; }

  bool IsSuccess() { return is_success_; }
  void SetIsSucces(bool ok) { is_success_ = ok; }

 private:
  std::string error_message_;
  bool is_success_;
};
}  // namespace s21

#endif  // MODEL_FACADE_OPERATION_RESULT_H

; ModuleID = 'global'
source_filename = "global"

@.str.0 = private constant [107 x i8] c"hello world!\0A\0AThis now supports escape codes! Here is a quote to prove it: \22, thanks for tuning in.\0A\09Bye!\0A\00"

define i32 @main() {
entry:
  %calltmp = call i32 (ptr, ...) @printf(ptr @.str.0)
  ret i32 0
}

declare i32 @printf(ptr, ...)

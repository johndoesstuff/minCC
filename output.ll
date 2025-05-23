; ModuleID = 'global'
source_filename = "global"

@.str.0 = private constant [14 x i8] c"hello world\\n\00"

define i32 @main() {
entry:
  %calltmp = call i32 (ptr, ...) @printf(ptr @.str.0)
  ret i32 0
}

declare i32 @printf(ptr, ...)

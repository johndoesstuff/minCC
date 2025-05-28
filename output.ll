; ModuleID = 'global'
source_filename = "global"

@.str.0 = private constant [12 x i8] c"hello world\00"
@.str.1 = private constant [4 x i8] c"%s\0A\00"
@.str.2 = private constant [4 x i8] c"%s\0A\00"

declare i32 @printf(ptr, ...)

declare float @fmodf(float, float)

declare double @fmod(double, double)

declare float @floorf(float)

define i32 @main() {
entry:
  %b = alloca ptr, align 8
  store ptr @.str.0, ptr %b, align 8
  %loadtmp = load ptr, ptr %b, align 8
  %calltmp = call i32 (ptr, ...) @printf(ptr @.str.1, ptr %loadtmp)
  %loadtmp1 = load ptr, ptr %b, align 8
  store i8 99, ptr %loadtmp1, align 1
  %loadtmp2 = load ptr, ptr %b, align 8
  %calltmp3 = call i32 (ptr, ...) @printf(ptr @.str.2, ptr %loadtmp2)
  ret i32 0
}

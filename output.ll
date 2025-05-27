; ModuleID = 'global'
source_filename = "global"

@.str.0 = private constant [6 x i8] c"hello\00"
@.str.1 = private constant [4 x i8] c"%c\0A\00"
@.str.2 = private constant [4 x i8] c"%c\0A\00"

define i32 @main() {
entry:
  %str = alloca ptr, align 8
  store ptr @.str.0, ptr %str, align 8
  %loadtmp = load ptr, ptr %str, align 8
  %deref = load ptr, ptr %loadtmp, align 8
  %calltmp = call i32 (ptr, ...) @printf(ptr @.str.1, ptr %deref)
  %loadtmp1 = load ptr, ptr %str, align 8
  %ptradd = getelementptr i8, ptr %loadtmp1, i32 2
  %deref2 = load ptr, ptr %ptradd, align 8
  %calltmp3 = call i32 (ptr, ...) @printf(ptr @.str.2, ptr %deref2)
  ret i32 0
}

declare i32 @printf(ptr, ...)

declare float @fmodf(float, float)

declare float @floorf(float)

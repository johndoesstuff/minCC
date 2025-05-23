; ModuleID = 'global'
source_filename = "global"

@.str.0 = private constant [12 x i8] c"hello world\00"

define i32 @main() {
entry:
  %test1 = alloca i8, align 1
  store i8 91, ptr %test1, align 1
  store i8 96, ptr %test1, align 1
  %test2 = alloca i8, align 1
  store i8 98, ptr %test2, align 1
  %loadtmp = load i8, ptr %test2, align 1
  %sext = sext i8 %loadtmp to i32
  %addtmp = add i32 %sext, 5
  %trunc = trunc i32 %addtmp to i8
  store i8 %trunc, ptr %test2, align 1
  %test3 = alloca ptr, align 8
  store ptr @.str.0, ptr %test3, align 8
  %test4 = alloca i8, align 1
  store i8 10, ptr %test4, align 1
  ret i32 0
}

declare i32 @printf(ptr, ...)

; ModuleID = 'tiny'
source_filename = "tiny"

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
  ret i32 0
}

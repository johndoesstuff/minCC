; ModuleID = 'tiny'
source_filename = "tiny"

define i32 @main() {
entry:
  %test1 = alloca i8, align 1
  store i8 91, ptr %test1, align 1
  store i8 96, ptr %test1, align 1
  %test2 = alloca i8, align 1
  store i8 98, ptr %test2, align 1
  ret i32 0
}

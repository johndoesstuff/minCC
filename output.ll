; ModuleID = 'tiny'
source_filename = "tiny"

define i32 @main() {
entry:
  %test1 = alloca i8, align 1
  store i32 4, ptr %test1, align 4
  ret i32 0
}

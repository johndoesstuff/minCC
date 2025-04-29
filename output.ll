; ModuleID = 'tiny'
source_filename = "tiny"

define i32 @main() {
entry:
  %x = alloca i1, align 1
  store i32 2, ptr %x, align 4
  %y = alloca i32, align 4
  store i32 3, ptr %y, align 4
}

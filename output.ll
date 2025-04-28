; ModuleID = 'tiny'
source_filename = "tiny"

define i32 @main() {
entry:
  %x = alloca i32, align 4
  store i32 2, ptr %x, align 4
  %loadtmp = load i32, ptr %x, align 4
  %multmp = mul i32 %loadtmp, 7
  %y = alloca i32, align 4
  store i32 %multmp, ptr %y, align 4
  %loadtmp1 = load i32, ptr %y, align 4
  ret i32 %loadtmp1
}

; ModuleID = 'tiny'
source_filename = "tiny"

define i32 @main() {
entry:
  %x = alloca i32, align 4
  store i32 3, ptr %x, align 4
  %loadtmp = load i32, ptr %x, align 4
  %multmp = mul i32 %loadtmp, 3
  ret i32 %multmp
}

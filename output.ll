; ModuleID = 'global'
source_filename = "global"

define i32 @main() {
entry:
  %calltmp = call i32 @foo(i32 5, i32 3)
  ret i32 %calltmp
}

define i32 @foo(i32 %a, i32 %b) {
entry:
  %a1 = alloca i32, align 4
  store i32 %a, ptr %a1, align 4
  %b2 = alloca i32, align 4
  store i32 %b, ptr %b2, align 4
  %loadtmp = load i32, ptr %a1, align 4
  %loadtmp3 = load i32, ptr %b2, align 4
  %multmp = mul i32 %loadtmp, %loadtmp3
  %loadtmp4 = load i32, ptr %a1, align 4
  %addtmp = add i32 %multmp, %loadtmp4
  %loadtmp5 = load i32, ptr %b2, align 4
  %addtmp6 = add i32 %addtmp, %loadtmp5
  ret i32 %addtmp6
}

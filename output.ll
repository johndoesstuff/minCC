; ModuleID = 'global'
source_filename = "global"

define i32 @main() {
entry:
  %a = alloca float, align 4
  store float 0x3FDA3D70A0000000, ptr %a, align 4
  %b = alloca float, align 4
  store float 0x3F847AE140000000, ptr %b, align 4
  %loadtmp = load float, ptr %a, align 4
  %loadtmp1 = load float, ptr %b, align 4
  %faddtmp = fadd float %loadtmp, %loadtmp1
  %c = alloca float, align 4
  store float %faddtmp, ptr %c, align 4
  %loadtmp2 = load float, ptr %c, align 4
  %loadtmp3 = load float, ptr %c, align 4
  %fmultmp = fmul float %loadtmp2, %loadtmp3
  store float %fmultmp, ptr %c, align 4
  ret i32 0
}

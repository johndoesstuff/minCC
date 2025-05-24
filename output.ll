; ModuleID = 'global'
source_filename = "global"

@.str.0 = private constant [36 x i8] c"Basic Raymarcher with Sphere SDF:\0A\0A\00"
@.str.1 = private constant [2 x i8] c"X\00"
@.str.2 = private constant [2 x i8] c".\00"
@.str.3 = private constant [2 x i8] c"\0A\00"
@.str.4 = private constant [2 x i8] c"\0A\00"

define i32 @main() {
entry:
  %calltmp = call i32 (ptr, ...) @printf(ptr @.str.0)
  %width = alloca i32, align 4
  store i32 100, ptr %width, align 4
  %height = alloca i32, align 4
  store i32 50, ptr %height, align 4
  %y = alloca i32, align 4
  store i32 0, ptr %y, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.end4, %entry
  %loadtmp = load i32, ptr %y, align 4
  %loadtmp1 = load i32, ptr %height, align 4
  %cmptmp = icmp slt i32 %loadtmp, %loadtmp1
  br i1 %cmptmp, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %x = alloca i32, align 4
  store i32 0, ptr %x, align 4
  br label %while.cond2

while.end:                                        ; preds = %while.cond
  %calltmp26 = call i32 (ptr, ...) @printf(ptr @.str.4)
  ret i32 0

while.cond2:                                      ; preds = %if.end, %while.body
  %loadtmp5 = load i32, ptr %x, align 4
  %loadtmp6 = load i32, ptr %width, align 4
  %cmptmp7 = icmp slt i32 %loadtmp5, %loadtmp6
  br i1 %cmptmp7, label %while.body3, label %while.end4

while.body3:                                      ; preds = %while.cond2
  %loadtmp8 = load i32, ptr %x, align 4
  %loadtmp9 = load i32, ptr %width, align 4
  %sitofp_tmp = sitofp i32 %loadtmp9 to float
  %fdivtmp = fdiv float 1.000000e+00, %sitofp_tmp
  %sitofp_tmp10 = sitofp i32 %loadtmp8 to float
  %fmultmp = fmul float %sitofp_tmp10, %fdivtmp
  %fsubtmp = fsub float %fmultmp, 5.000000e-01
  %dirX = alloca float, align 4
  store float %fsubtmp, ptr %dirX, align 4
  %loadtmp11 = load i32, ptr %y, align 4
  %loadtmp12 = load i32, ptr %height, align 4
  %sitofp_tmp13 = sitofp i32 %loadtmp12 to float
  %fdivtmp14 = fdiv float 1.000000e+00, %sitofp_tmp13
  %sitofp_tmp15 = sitofp i32 %loadtmp11 to float
  %fmultmp16 = fmul float %sitofp_tmp15, %fdivtmp14
  %fsubtmp17 = fsub float %fmultmp16, 5.000000e-01
  %dirY = alloca float, align 4
  store float %fsubtmp17, ptr %dirY, align 4
  %loadtmp18 = load float, ptr %dirX, align 4
  %cmptmp19 = fcmp ogt float %loadtmp18, 0.000000e+00
  br i1 %cmptmp19, label %if.then, label %if.else

while.end4:                                       ; preds = %while.cond2
  %calltmp23 = call i32 (ptr, ...) @printf(ptr @.str.3)
  %loadtmp24 = load i32, ptr %y, align 4
  %addtmp25 = add i32 %loadtmp24, 1
  store i32 %addtmp25, ptr %y, align 4
  br label %while.cond

if.then:                                          ; preds = %while.body3
  %calltmp20 = call i32 (ptr, ...) @printf(ptr @.str.1)
  br label %if.end

if.else:                                          ; preds = %while.body3
  %calltmp21 = call i32 (ptr, ...) @printf(ptr @.str.2)
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %loadtmp22 = load i32, ptr %x, align 4
  %addtmp = add i32 %loadtmp22, 1
  store i32 %addtmp, ptr %x, align 4
  br label %while.cond2
}

declare i32 @printf(ptr, ...)

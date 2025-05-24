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
  %calltmp46 = call i32 (ptr, ...) @printf(ptr @.str.4)
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
  %dirZ = alloca float, align 4
  store float 1.000000e+00, ptr %dirZ, align 4
  %loadtmp18 = load float, ptr %dirX, align 4
  %loadtmp19 = load float, ptr %dirX, align 4
  %fmultmp20 = fmul float %loadtmp18, %loadtmp19
  %loadtmp21 = load float, ptr %dirY, align 4
  %loadtmp22 = load float, ptr %dirY, align 4
  %fmultmp23 = fmul float %loadtmp21, %loadtmp22
  %faddtmp = fadd float %fmultmp20, %fmultmp23
  %loadtmp24 = load float, ptr %dirZ, align 4
  %loadtmp25 = load float, ptr %dirZ, align 4
  %fmultmp26 = fmul float %loadtmp24, %loadtmp25
  %faddtmp27 = fadd float %faddtmp, %fmultmp26
  %calltmp28 = call float @sqrt_approx(float %faddtmp27)
  %norm = alloca float, align 4
  store float %calltmp28, ptr %norm, align 4
  %loadtmp29 = load float, ptr %dirX, align 4
  %loadtmp30 = load float, ptr %norm, align 4
  %fdivtmp31 = fdiv float %loadtmp29, %loadtmp30
  store float %fdivtmp31, ptr %dirX, align 4
  %loadtmp32 = load float, ptr %dirY, align 4
  %loadtmp33 = load float, ptr %norm, align 4
  %fdivtmp34 = fdiv float %loadtmp32, %loadtmp33
  store float %fdivtmp34, ptr %dirY, align 4
  %loadtmp35 = load float, ptr %dirZ, align 4
  %loadtmp36 = load float, ptr %norm, align 4
  %fdivtmp37 = fdiv float %loadtmp35, %loadtmp36
  store float %fdivtmp37, ptr %dirZ, align 4
  %loadtmp38 = load float, ptr %dirX, align 4
  %cmptmp39 = fcmp ogt float %loadtmp38, 0.000000e+00
  br i1 %cmptmp39, label %if.then, label %if.else

while.end4:                                       ; preds = %while.cond2
  %calltmp43 = call i32 (ptr, ...) @printf(ptr @.str.3)
  %loadtmp44 = load i32, ptr %y, align 4
  %addtmp45 = add i32 %loadtmp44, 1
  store i32 %addtmp45, ptr %y, align 4
  br label %while.cond

if.then:                                          ; preds = %while.body3
  %calltmp40 = call i32 (ptr, ...) @printf(ptr @.str.1)
  br label %if.end

if.else:                                          ; preds = %while.body3
  %calltmp41 = call i32 (ptr, ...) @printf(ptr @.str.2)
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %loadtmp42 = load i32, ptr %x, align 4
  %addtmp = add i32 %loadtmp42, 1
  store i32 %addtmp, ptr %x, align 4
  br label %while.cond2
}

declare i32 @printf(ptr, ...)

define float @sqrt_approx(float %x) {
entry:
  %x1 = alloca float, align 4
  store float %x, ptr %x1, align 4
  %loadtmp = load float, ptr %x1, align 4
  %cmptmp = fcmp olt float %loadtmp, 0.000000e+00
  br i1 %cmptmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  ret float -1.000000e+00
  br label %if.end

if.end:                                           ; preds = %if.then, %entry
  %loadtmp4 = load float, ptr %x1, align 4
  %cmptmp5 = fcmp oeq float %loadtmp4, 0.000000e+00
  br i1 %cmptmp5, label %if.then2, label %if.end3

if.then2:                                         ; preds = %if.end
  ret float 0.000000e+00
  br label %if.end3

if.end3:                                          ; preds = %if.then2, %if.end
  %loadtmp6 = load float, ptr %x1, align 4
  %fdivtmp = fdiv float %loadtmp6, 2.000000e+00
  %guess = alloca float, align 4
  store float %fdivtmp, ptr %guess, align 4
  %epsilon = alloca float, align 4
  store float 0x3EE4F8B580000000, ptr %epsilon, align 4
  %i = alloca i32, align 4
  store i32 0, ptr %i, align 4
  br label %while.cond

while.cond:                                       ; preds = %if.end14, %if.end3
  %loadtmp7 = load i32, ptr %i, align 4
  %cmptmp8 = icmp slt i32 %loadtmp7, 20
  br i1 %cmptmp8, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %loadtmp9 = load float, ptr %guess, align 4
  %loadtmp10 = load float, ptr %x1, align 4
  %loadtmp11 = load float, ptr %guess, align 4
  %fdivtmp12 = fdiv float %loadtmp10, %loadtmp11
  %faddtmp = fadd float %loadtmp9, %fdivtmp12
  %fmultmp = fmul float 5.000000e-01, %faddtmp
  %next = alloca float, align 4
  store float %fmultmp, ptr %next, align 4
  %loadtmp15 = load float, ptr %guess, align 4
  %loadtmp16 = load float, ptr %next, align 4
  %fsubtmp = fsub float %loadtmp15, %loadtmp16
  %loadtmp17 = load float, ptr %epsilon, align 4
  %cmptmp18 = fcmp olt float %fsubtmp, %loadtmp17
  %loadtmp19 = load float, ptr %guess, align 4
  %loadtmp20 = load float, ptr %next, align 4
  %fsubtmp21 = fsub float %loadtmp19, %loadtmp20
  %loadtmp22 = load float, ptr %epsilon, align 4
  %fnegtmp = fsub float 0.000000e+00, %loadtmp22
  %cmptmp23 = fcmp ogt float %fsubtmp21, %fnegtmp
  br i1 %cmptmp18, label %and.rhs, label %and.end

while.end:                                        ; preds = %while.cond
  %loadtmp26 = load float, ptr %guess, align 4
  ret float %loadtmp26

if.then13:                                        ; preds = %and.end
  store i32 20, ptr %i, align 4
  br label %if.end14

if.else:                                          ; preds = %and.end
  %loadtmp24 = load float, ptr %next, align 4
  store float %loadtmp24, ptr %guess, align 4
  %loadtmp25 = load i32, ptr %i, align 4
  %addtmp = add i32 %loadtmp25, 1
  store i32 %addtmp, ptr %i, align 4
  br label %if.end14

if.end14:                                         ; preds = %if.else, %if.then13
  br label %while.cond

and.rhs:                                          ; preds = %while.body
  br label %and.end

and.end:                                          ; preds = %and.rhs, %while.body
  %andtmp = phi i1 [ %cmptmp18, %while.body ], [ %cmptmp23, %and.rhs ]
  br i1 %andtmp, label %if.then13, label %if.else
}

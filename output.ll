; ModuleID = 'global'
source_filename = "global"

@.str.0 = private constant [36 x i8] c"Basic Raymarcher with Sphere SDF:\0A\0A\00"
@.str.1 = private constant [2 x i8] c" \00"
@.str.2 = private constant [2 x i8] c"#\00"
@.str.3 = private constant [2 x i8] c"=\00"
@.str.4 = private constant [2 x i8] c"-\00"
@.str.5 = private constant [2 x i8] c"'\00"
@.str.6 = private constant [2 x i8] c".\00"
@.str.7 = private constant [2 x i8] c"\0A\00"
@.str.8 = private constant [2 x i8] c"\0A\00"

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
  %calltmp74 = call i32 (ptr, ...) @printf(ptr @.str.8)
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
  %loadtmp39 = load float, ptr %dirY, align 4
  %loadtmp40 = load float, ptr %dirZ, align 4
  %calltmp41 = call float @march_ray(float 0.000000e+00, float 0.000000e+00, float 0.000000e+00, float %loadtmp38, float %loadtmp39, float %loadtmp40)
  %hit = alloca float, align 4
  store float %calltmp41, ptr %hit, align 4
  %loadtmp42 = load float, ptr %hit, align 4
  %cmptmp43 = fcmp oeq float %loadtmp42, 0.000000e+00
  br i1 %cmptmp43, label %if.then, label %if.else

while.end4:                                       ; preds = %while.cond2
  %calltmp71 = call i32 (ptr, ...) @printf(ptr @.str.7)
  %loadtmp72 = load i32, ptr %y, align 4
  %addtmp73 = add i32 %loadtmp72, 1
  store i32 %addtmp73, ptr %y, align 4
  br label %while.cond

if.then:                                          ; preds = %while.body3
  %calltmp44 = call i32 (ptr, ...) @printf(ptr @.str.1)
  br label %if.end

if.else:                                          ; preds = %while.body3
  %loadtmp48 = load float, ptr %hit, align 4
  %cmptmp49 = fcmp olt float %loadtmp48, 2.000000e+00
  br i1 %cmptmp49, label %if.then45, label %if.else46

if.end:                                           ; preds = %if.then
  %loadtmp70 = load i32, ptr %x, align 4
  %addtmp = add i32 %loadtmp70, 1
  store i32 %addtmp, ptr %x, align 4
  br label %while.cond2

if.then45:                                        ; preds = %if.else
  %calltmp50 = call i32 (ptr, ...) @printf(ptr @.str.2)
  br label %if.end47

if.else46:                                        ; preds = %if.else
  %loadtmp54 = load float, ptr %hit, align 4
  %cmptmp55 = fcmp olt float %loadtmp54, 5.000000e+00
  br i1 %cmptmp55, label %if.then51, label %if.else52

if.end47:                                         ; preds = %if.then45

if.then51:                                        ; preds = %if.else46
  %calltmp56 = call i32 (ptr, ...) @printf(ptr @.str.3)
  br label %if.end53

if.else52:                                        ; preds = %if.else46
  %loadtmp60 = load float, ptr %hit, align 4
  %cmptmp61 = fcmp olt float %loadtmp60, 1.000000e+01
  br i1 %cmptmp61, label %if.then57, label %if.else58

if.end53:                                         ; preds = %if.then51

if.then57:                                        ; preds = %if.else52
  %calltmp62 = call i32 (ptr, ...) @printf(ptr @.str.4)
  br label %if.end59

if.else58:                                        ; preds = %if.else52
  %loadtmp66 = load float, ptr %hit, align 4
  %cmptmp67 = fcmp olt float %loadtmp66, 2.500000e+01
  br i1 %cmptmp67, label %if.then63, label %if.else64

if.end59:                                         ; preds = %if.then57

if.then63:                                        ; preds = %if.else58
  %calltmp68 = call i32 (ptr, ...) @printf(ptr @.str.5)
  br label %if.end65

if.else64:                                        ; preds = %if.else58
  %calltmp69 = call i32 (ptr, ...) @printf(ptr @.str.6)
  br label %if.end65

if.end65:                                         ; preds = %if.else64, %if.then63
}

declare i32 @printf(ptr, ...)

declare float @fmodf(float, float)

declare float @floorf(float)

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

define float @sdf_sphere(float %px, float %py, float %pz, float %cx, float %cy, float %cz, float %radius) {
entry:
  %px1 = alloca float, align 4
  store float %px, ptr %px1, align 4
  %py2 = alloca float, align 4
  store float %py, ptr %py2, align 4
  %pz3 = alloca float, align 4
  store float %pz, ptr %pz3, align 4
  %cx4 = alloca float, align 4
  store float %cx, ptr %cx4, align 4
  %cy5 = alloca float, align 4
  store float %cy, ptr %cy5, align 4
  %cz6 = alloca float, align 4
  store float %cz, ptr %cz6, align 4
  %radius7 = alloca float, align 4
  store float %radius, ptr %radius7, align 4
  %loadtmp = load float, ptr %px1, align 4
  %loadtmp8 = load float, ptr %cx4, align 4
  %fsubtmp = fsub float %loadtmp, %loadtmp8
  %dx = alloca float, align 4
  store float %fsubtmp, ptr %dx, align 4
  %loadtmp9 = load float, ptr %py2, align 4
  %loadtmp10 = load float, ptr %cy5, align 4
  %fsubtmp11 = fsub float %loadtmp9, %loadtmp10
  %dy = alloca float, align 4
  store float %fsubtmp11, ptr %dy, align 4
  %loadtmp12 = load float, ptr %pz3, align 4
  %loadtmp13 = load float, ptr %cz6, align 4
  %fsubtmp14 = fsub float %loadtmp12, %loadtmp13
  %dz = alloca float, align 4
  store float %fsubtmp14, ptr %dz, align 4
  %loadtmp15 = load float, ptr %dx, align 4
  %loadtmp16 = load float, ptr %dx, align 4
  %fmultmp = fmul float %loadtmp15, %loadtmp16
  %loadtmp17 = load float, ptr %dy, align 4
  %loadtmp18 = load float, ptr %dy, align 4
  %fmultmp19 = fmul float %loadtmp17, %loadtmp18
  %faddtmp = fadd float %fmultmp, %fmultmp19
  %loadtmp20 = load float, ptr %dz, align 4
  %loadtmp21 = load float, ptr %dz, align 4
  %fmultmp22 = fmul float %loadtmp20, %loadtmp21
  %faddtmp23 = fadd float %faddtmp, %fmultmp22
  %calltmp = call float @sqrt_approx(float %faddtmp23)
  %loadtmp24 = load float, ptr %radius7, align 4
  %fsubtmp25 = fsub float %calltmp, %loadtmp24
  ret float %fsubtmp25
}

define float @march_ray(float %ox, float %oy, float %oz, float %dx, float %dy, float %dz) {
entry:
  %ox1 = alloca float, align 4
  store float %ox, ptr %ox1, align 4
  %oy2 = alloca float, align 4
  store float %oy, ptr %oy2, align 4
  %oz3 = alloca float, align 4
  store float %oz, ptr %oz3, align 4
  %dx4 = alloca float, align 4
  store float %dx, ptr %dx4, align 4
  %dy5 = alloca float, align 4
  store float %dy, ptr %dy5, align 4
  %dz6 = alloca float, align 4
  store float %dz, ptr %dz6, align 4
  %totalDist = alloca float, align 4
  store float 0.000000e+00, ptr %totalDist, align 4
  %steps = alloca i32, align 4
  store i32 0, ptr %steps, align 4
  br label %while.cond

while.cond:                                       ; preds = %if.end, %entry
  %loadtmp = load i32, ptr %steps, align 4
  %cmptmp = icmp slt i32 %loadtmp, 64
  %loadtmp7 = load float, ptr %totalDist, align 4
  %cmptmp8 = fcmp olt float %loadtmp7, 1.000000e+02
  br i1 %cmptmp, label %and.rhs, label %and.end

while.body:                                       ; preds = %and.end
  %loadtmp9 = load float, ptr %ox1, align 4
  %loadtmp10 = load float, ptr %dx4, align 4
  %loadtmp11 = load float, ptr %totalDist, align 4
  %fmultmp = fmul float %loadtmp10, %loadtmp11
  %faddtmp = fadd float %loadtmp9, %fmultmp
  %px = alloca float, align 4
  store float %faddtmp, ptr %px, align 4
  %loadtmp12 = load float, ptr %oy2, align 4
  %loadtmp13 = load float, ptr %dy5, align 4
  %loadtmp14 = load float, ptr %totalDist, align 4
  %fmultmp15 = fmul float %loadtmp13, %loadtmp14
  %faddtmp16 = fadd float %loadtmp12, %fmultmp15
  %py = alloca float, align 4
  store float %faddtmp16, ptr %py, align 4
  %loadtmp17 = load float, ptr %oz3, align 4
  %loadtmp18 = load float, ptr %dz6, align 4
  %loadtmp19 = load float, ptr %totalDist, align 4
  %fmultmp20 = fmul float %loadtmp18, %loadtmp19
  %faddtmp21 = fadd float %loadtmp17, %fmultmp20
  %pz = alloca float, align 4
  store float %faddtmp21, ptr %pz, align 4
  %loadtmp22 = load float, ptr %px, align 4
  %loadtmp23 = load float, ptr %py, align 4
  %loadtmp24 = load float, ptr %pz, align 4
  %calltmp = call float @sdf_sphere(float %loadtmp22, float %loadtmp23, float %loadtmp24, float 0.000000e+00, float 0.000000e+00, float 3.000000e+00, float 1.000000e+00)
  %dist = alloca float, align 4
  store float %calltmp, ptr %dist, align 4
  %loadtmp25 = load float, ptr %dist, align 4
  %cmptmp26 = fcmp olt float %loadtmp25, 0x3F50624DE0000000
  br i1 %cmptmp26, label %if.then, label %if.end

while.end:                                        ; preds = %and.end
  ret float 0.000000e+00

and.rhs:                                          ; preds = %while.cond
  br label %and.end

and.end:                                          ; preds = %and.rhs, %while.cond
  %andtmp = phi i1 [ %cmptmp, %while.cond ], [ %cmptmp8, %and.rhs ]
  br i1 %andtmp, label %while.body, label %while.end

if.then:                                          ; preds = %while.body
  %loadtmp27 = load float, ptr %totalDist, align 4
  %loadtmp28 = load float, ptr %dist, align 4
  %faddtmp29 = fadd float %loadtmp27, %loadtmp28
  ret float %faddtmp29
  br label %if.end

if.end:                                           ; preds = %if.then, %while.body
  %loadtmp30 = load float, ptr %totalDist, align 4
  %loadtmp31 = load float, ptr %dist, align 4
  %faddtmp32 = fadd float %loadtmp30, %loadtmp31
  store float %faddtmp32, ptr %totalDist, align 4
  %loadtmp33 = load i32, ptr %steps, align 4
  %addtmp = add i32 %loadtmp33, 1
  store i32 %addtmp, ptr %steps, align 4
  br label %while.cond
}

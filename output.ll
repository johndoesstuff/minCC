; ModuleID = 'global'
source_filename = "global"

@.str.0 = private constant [36 x i8] c"Basic Raymarcher with Sphere SDF:\0A\0A\00"
@.str.1 = private constant [2 x i8] c" \00"
@.str.2 = private constant [2 x i8] c"#\00"
@.str.3 = private constant [2 x i8] c"=\00"
@.str.4 = private constant [2 x i8] c"+\00"
@.str.5 = private constant [2 x i8] c"-\00"
@.str.6 = private constant [2 x i8] c"'\00"
@.str.7 = private constant [2 x i8] c".\00"
@.str.8 = private constant [2 x i8] c"\0A\00"
@.str.9 = private constant [2 x i8] c"\0A\00"

define i32 @main() {
entry:
  %calltmp = call i32 (ptr, ...) @printf(ptr @.str.0)
  %width = alloca i32, align 4
  store i32 100, ptr %width, align 4
  %height = alloca i32, align 4
  store i32 50, ptr %height, align 4
  %cameraZ = alloca float, align 4
  store float 4.000000e+00, ptr %cameraZ, align 4
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
  %calltmp81 = call i32 (ptr, ...) @printf(ptr @.str.9)
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
  %loadtmp38 = load float, ptr %cameraZ, align 4
  %fnegtmp = fsub float 0.000000e+00, %loadtmp38
  %loadtmp39 = load float, ptr %dirX, align 4
  %loadtmp40 = load float, ptr %dirY, align 4
  %loadtmp41 = load float, ptr %dirZ, align 4
  %calltmp42 = call float @march_ray(float 0.000000e+00, float 0.000000e+00, float %fnegtmp, float %loadtmp39, float %loadtmp40, float %loadtmp41)
  %hit = alloca float, align 4
  store float %calltmp42, ptr %hit, align 4
  %loadtmp43 = load float, ptr %hit, align 4
  %cmptmp44 = fcmp oeq float %loadtmp43, 0.000000e+00
  br i1 %cmptmp44, label %if.then, label %if.else

while.end4:                                       ; preds = %while.cond2
  %calltmp78 = call i32 (ptr, ...) @printf(ptr @.str.8)
  %loadtmp79 = load i32, ptr %y, align 4
  %addtmp80 = add i32 %loadtmp79, 1
  store i32 %addtmp80, ptr %y, align 4
  br label %while.cond

if.then:                                          ; preds = %while.body3
  %calltmp45 = call i32 (ptr, ...) @printf(ptr @.str.1)
  br label %if.end

if.else:                                          ; preds = %while.body3
  %loadtmp49 = load float, ptr %hit, align 4
  %cmptmp50 = fcmp olt float %loadtmp49, 4.000000e+00
  br i1 %cmptmp50, label %if.then46, label %if.else47

if.end:                                           ; preds = %if.end48, %if.then
  %loadtmp77 = load i32, ptr %x, align 4
  %addtmp = add i32 %loadtmp77, 1
  store i32 %addtmp, ptr %x, align 4
  br label %while.cond2

if.then46:                                        ; preds = %if.else
  %calltmp51 = call i32 (ptr, ...) @printf(ptr @.str.2)
  br label %if.end48

if.else47:                                        ; preds = %if.else
  %loadtmp55 = load float, ptr %hit, align 4
  %cmptmp56 = fcmp olt float %loadtmp55, 6.000000e+00
  br i1 %cmptmp56, label %if.then52, label %if.else53

if.end48:                                         ; preds = %if.end54, %if.then46
  br label %if.end

if.then52:                                        ; preds = %if.else47
  %calltmp57 = call i32 (ptr, ...) @printf(ptr @.str.3)
  br label %if.end54

if.else53:                                        ; preds = %if.else47
  %loadtmp61 = load float, ptr %hit, align 4
  %cmptmp62 = fcmp olt float %loadtmp61, 1.000000e+01
  br i1 %cmptmp62, label %if.then58, label %if.else59

if.end54:                                         ; preds = %if.end60, %if.then52
  br label %if.end48

if.then58:                                        ; preds = %if.else53
  %calltmp63 = call i32 (ptr, ...) @printf(ptr @.str.4)
  br label %if.end60

if.else59:                                        ; preds = %if.else53
  %loadtmp67 = load float, ptr %hit, align 4
  %cmptmp68 = fcmp olt float %loadtmp67, 1.500000e+01
  br i1 %cmptmp68, label %if.then64, label %if.else65

if.end60:                                         ; preds = %if.end66, %if.then58
  br label %if.end54

if.then64:                                        ; preds = %if.else59
  %calltmp69 = call i32 (ptr, ...) @printf(ptr @.str.5)
  br label %if.end66

if.else65:                                        ; preds = %if.else59
  %loadtmp73 = load float, ptr %hit, align 4
  %cmptmp74 = fcmp olt float %loadtmp73, 2.000000e+01
  br i1 %cmptmp74, label %if.then70, label %if.else71

if.end66:                                         ; preds = %if.end72, %if.then64
  br label %if.end60

if.then70:                                        ; preds = %if.else65
  %calltmp75 = call i32 (ptr, ...) @printf(ptr @.str.6)
  br label %if.end72

if.else71:                                        ; preds = %if.else65
  %calltmp76 = call i32 (ptr, ...) @printf(ptr @.str.7)
  br label %if.end72

if.end72:                                         ; preds = %if.else71, %if.then70
  br label %if.end66
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

if.end:                                           ; preds = %entry
  %loadtmp4 = load float, ptr %x1, align 4
  %cmptmp5 = fcmp oeq float %loadtmp4, 0.000000e+00
  br i1 %cmptmp5, label %if.then2, label %if.end3

if.then2:                                         ; preds = %if.end
  ret float 0.000000e+00

if.end3:                                          ; preds = %if.end
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

define float @sdf(float %px, float %py, float %pz) {
entry:
  %px1 = alloca float, align 4
  store float %px, ptr %px1, align 4
  %py2 = alloca float, align 4
  store float %py, ptr %py2, align 4
  %pz3 = alloca float, align 4
  store float %pz, ptr %pz3, align 4
  %spacing = alloca float, align 4
  store float 3.000000e+00, ptr %spacing, align 4
  %loadtmp = load float, ptr %px1, align 4
  %loadtmp4 = load float, ptr %spacing, align 4
  %fmultmp = fmul float %loadtmp4, 5.000000e-01
  %faddtmp = fadd float %loadtmp, %fmultmp
  %loadtmp5 = load float, ptr %spacing, align 4
  %calltmp = call float @fmodf(float %faddtmp, float %loadtmp5)
  %rx = alloca float, align 4
  store float %calltmp, ptr %rx, align 4
  %loadtmp6 = load float, ptr %rx, align 4
  %cmptmp = fcmp olt float %loadtmp6, 0.000000e+00
  br i1 %cmptmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %loadtmp7 = load float, ptr %rx, align 4
  %loadtmp8 = load float, ptr %spacing, align 4
  %faddtmp9 = fadd float %loadtmp7, %loadtmp8
  store float %faddtmp9, ptr %rx, align 4
  br label %if.end

if.end:                                           ; preds = %if.then, %entry
  %loadtmp10 = load float, ptr %rx, align 4
  %loadtmp11 = load float, ptr %spacing, align 4
  %fmultmp12 = fmul float %loadtmp11, 5.000000e-01
  %fsubtmp = fsub float %loadtmp10, %fmultmp12
  store float %fsubtmp, ptr %rx, align 4
  %loadtmp13 = load float, ptr %py2, align 4
  %loadtmp14 = load float, ptr %spacing, align 4
  %fmultmp15 = fmul float %loadtmp14, 5.000000e-01
  %faddtmp16 = fadd float %loadtmp13, %fmultmp15
  %loadtmp17 = load float, ptr %spacing, align 4
  %calltmp18 = call float @fmodf(float %faddtmp16, float %loadtmp17)
  %ry = alloca float, align 4
  store float %calltmp18, ptr %ry, align 4
  %loadtmp21 = load float, ptr %ry, align 4
  %cmptmp22 = fcmp olt float %loadtmp21, 0.000000e+00
  br i1 %cmptmp22, label %if.then19, label %if.end20

if.then19:                                        ; preds = %if.end
  %loadtmp23 = load float, ptr %ry, align 4
  %loadtmp24 = load float, ptr %spacing, align 4
  %faddtmp25 = fadd float %loadtmp23, %loadtmp24
  store float %faddtmp25, ptr %ry, align 4
  br label %if.end20

if.end20:                                         ; preds = %if.then19, %if.end
  %loadtmp26 = load float, ptr %ry, align 4
  %loadtmp27 = load float, ptr %spacing, align 4
  %fmultmp28 = fmul float %loadtmp27, 5.000000e-01
  %fsubtmp29 = fsub float %loadtmp26, %fmultmp28
  store float %fsubtmp29, ptr %ry, align 4
  %loadtmp30 = load float, ptr %pz3, align 4
  %loadtmp31 = load float, ptr %spacing, align 4
  %fmultmp32 = fmul float %loadtmp31, 5.000000e-01
  %faddtmp33 = fadd float %loadtmp30, %fmultmp32
  %loadtmp34 = load float, ptr %spacing, align 4
  %calltmp35 = call float @fmodf(float %faddtmp33, float %loadtmp34)
  %loadtmp36 = load float, ptr %spacing, align 4
  %fmultmp37 = fmul float %loadtmp36, 5.000000e-01
  %fsubtmp38 = fsub float %calltmp35, %fmultmp37
  %rz = alloca float, align 4
  store float %fsubtmp38, ptr %rz, align 4
  %loadtmp39 = load float, ptr %rx, align 4
  %loadtmp40 = load float, ptr %ry, align 4
  %loadtmp41 = load float, ptr %rz, align 4
  %calltmp42 = call float @sdf_sphere(float %loadtmp39, float %loadtmp40, float %loadtmp41, float 0.000000e+00, float 0.000000e+00, float 0.000000e+00, float 1.000000e+00)
  ret float %calltmp42
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
  %cmptmp = icmp slt i32 %loadtmp, 35
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
  %calltmp = call float @sdf(float %loadtmp22, float %loadtmp23, float %loadtmp24)
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

if.end:                                           ; preds = %while.body
  %loadtmp30 = load float, ptr %totalDist, align 4
  %loadtmp31 = load float, ptr %dist, align 4
  %faddtmp32 = fadd float %loadtmp30, %loadtmp31
  store float %faddtmp32, ptr %totalDist, align 4
  %loadtmp33 = load i32, ptr %steps, align 4
  %addtmp = add i32 %loadtmp33, 1
  store i32 %addtmp, ptr %steps, align 4
  br label %while.cond
}

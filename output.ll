; ModuleID = 'global'
source_filename = "global"

@.str.0 = private constant [36 x i8] c"Basic Raymarcher with Sphere SDF:\0A\0A\00"
@.str.1 = private constant [92 x i8] c"@&%QWNM0gB$#DR8mHXKAUbGOpV4d9h6PkqwSE2]ayjxY5Zoen[ult13If}C{iF|(7J)vTLs?z/*cr!+<>;=^,_:'-.`\00"
@.str.2 = private constant [2 x i8] c" \00"
@.str.3 = private constant [2 x i8] c" \00"
@.str.4 = private constant [3 x i8] c"%c\00"
@.str.5 = private constant [2 x i8] c"\0A\00"
@.str.6 = private constant [2 x i8] c"\0A\00"

define i32 @main() {
entry:
  %calltmp = call i32 (ptr, ...) @printf(ptr @.str.0)
  %width = alloca i32, align 4
  store i32 100, ptr %width, align 4
  %height = alloca i32, align 4
  store i32 50, ptr %height, align 4
  %charset = alloca ptr, align 8
  store ptr @.str.1, ptr %charset, align 8
  %cameraZ = alloca double, align 8
  store double 4.000000e+00, ptr %cameraZ, align 8
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
  %calltmp72 = call i32 (ptr, ...) @printf(ptr @.str.6)
  ret i32 0

while.cond2:                                      ; preds = %if.end, %while.body
  %loadtmp5 = load i32, ptr %x, align 4
  %loadtmp6 = load i32, ptr %width, align 4
  %cmptmp7 = icmp slt i32 %loadtmp5, %loadtmp6
  br i1 %cmptmp7, label %while.body3, label %while.end4

while.body3:                                      ; preds = %while.cond2
  %loadtmp8 = load i32, ptr %x, align 4
  %loadtmp9 = load i32, ptr %width, align 4
  %sitofp_tmp = sitofp i32 %loadtmp9 to double
  %fdivtmp = fdiv double 1.000000e+00, %sitofp_tmp
  %sitofp_tmp10 = sitofp i32 %loadtmp8 to double
  %fmultmp = fmul double %sitofp_tmp10, %fdivtmp
  %fsubtmp = fsub double %fmultmp, 5.000000e-01
  %dirX = alloca double, align 8
  store double %fsubtmp, ptr %dirX, align 8
  %loadtmp11 = load i32, ptr %y, align 4
  %loadtmp12 = load i32, ptr %height, align 4
  %sitofp_tmp13 = sitofp i32 %loadtmp12 to double
  %fdivtmp14 = fdiv double 1.000000e+00, %sitofp_tmp13
  %sitofp_tmp15 = sitofp i32 %loadtmp11 to double
  %fmultmp16 = fmul double %sitofp_tmp15, %fdivtmp14
  %fsubtmp17 = fsub double %fmultmp16, 5.000000e-01
  %dirY = alloca double, align 8
  store double %fsubtmp17, ptr %dirY, align 8
  %dirZ = alloca double, align 8
  store double 1.000000e+00, ptr %dirZ, align 8
  %loadtmp18 = load double, ptr %dirX, align 8
  %loadtmp19 = load double, ptr %dirX, align 8
  %fmultmp20 = fmul double %loadtmp18, %loadtmp19
  %loadtmp21 = load double, ptr %dirY, align 8
  %loadtmp22 = load double, ptr %dirY, align 8
  %fmultmp23 = fmul double %loadtmp21, %loadtmp22
  %faddtmp = fadd double %fmultmp20, %fmultmp23
  %loadtmp24 = load double, ptr %dirZ, align 8
  %loadtmp25 = load double, ptr %dirZ, align 8
  %fmultmp26 = fmul double %loadtmp24, %loadtmp25
  %faddtmp27 = fadd double %faddtmp, %fmultmp26
  %calltmp28 = call double @sqrt_approx(double %faddtmp27)
  %norm = alloca double, align 8
  store double %calltmp28, ptr %norm, align 8
  %loadtmp29 = load double, ptr %dirX, align 8
  %loadtmp30 = load double, ptr %norm, align 8
  %fdivtmp31 = fdiv double %loadtmp29, %loadtmp30
  store double %fdivtmp31, ptr %dirX, align 8
  %loadtmp32 = load double, ptr %dirX, align 8
  %loadtmp33 = load double, ptr %dirY, align 8
  %loadtmp34 = load double, ptr %norm, align 8
  %fdivtmp35 = fdiv double %loadtmp33, %loadtmp34
  store double %fdivtmp35, ptr %dirY, align 8
  %loadtmp36 = load double, ptr %dirY, align 8
  %loadtmp37 = load double, ptr %dirZ, align 8
  %loadtmp38 = load double, ptr %norm, align 8
  %fdivtmp39 = fdiv double %loadtmp37, %loadtmp38
  store double %fdivtmp39, ptr %dirZ, align 8
  %loadtmp40 = load double, ptr %dirZ, align 8
  %loadtmp41 = load double, ptr %cameraZ, align 8
  %fnegtmp = fsub double 0.000000e+00, %loadtmp41
  %loadtmp42 = load double, ptr %dirX, align 8
  %loadtmp43 = load double, ptr %dirY, align 8
  %loadtmp44 = load double, ptr %dirZ, align 8
  %calltmp45 = call double @march_ray(double 0.000000e+00, double 0.000000e+00, double %fnegtmp, double %loadtmp42, double %loadtmp43, double %loadtmp44)
  %hit = alloca double, align 8
  store double %calltmp45, ptr %hit, align 8
  %loadtmp46 = load double, ptr %hit, align 8
  %cmptmp47 = fcmp oeq double %loadtmp46, 0.000000e+00
  br i1 %cmptmp47, label %if.then, label %if.else

while.end4:                                       ; preds = %while.cond2
  %calltmp67 = call i32 (ptr, ...) @printf(ptr @.str.5)
  %loadtmp68 = load i32, ptr %y, align 4
  %addtmp69 = add i32 %loadtmp68, 1
  store i32 %addtmp69, ptr %y, align 4
  %loadtmp70 = load i32, ptr %y, align 4
  %subtmp71 = sub i32 %loadtmp70, 1
  br label %while.cond

if.then:                                          ; preds = %while.body3
  %calltmp48 = call i32 (ptr, ...) @printf(ptr @.str.2)
  br label %if.end

if.else:                                          ; preds = %while.body3
  %charset_len = alloca i32, align 4
  store i32 91, ptr %charset_len, align 4
  %loadtmp49 = load double, ptr %hit, align 8
  %fdivtmp50 = fdiv double %loadtmp49, 2.000000e+01
  %loadtmp51 = load i32, ptr %charset_len, align 4
  %subtmp = sub i32 %loadtmp51, 1
  %sitofp_tmp52 = sitofp i32 %subtmp to double
  %fmultmp53 = fmul double %fdivtmp50, %sitofp_tmp52
  %fptosi = fptosi double %fmultmp53 to i32
  %index = alloca i32, align 4
  store i32 %fptosi, ptr %index, align 4
  %loadtmp57 = load i32, ptr %index, align 4
  %loadtmp58 = load i32, ptr %charset_len, align 4
  %cmptmp59 = icmp sge i32 %loadtmp57, %loadtmp58
  br i1 %cmptmp59, label %if.then54, label %if.else55

if.end:                                           ; preds = %if.end56, %if.then
  %loadtmp64 = load i32, ptr %x, align 4
  %addtmp = add i32 %loadtmp64, 1
  store i32 %addtmp, ptr %x, align 4
  %loadtmp65 = load i32, ptr %x, align 4
  %subtmp66 = sub i32 %loadtmp65, 1
  br label %while.cond2

if.then54:                                        ; preds = %if.else
  %calltmp60 = call i32 (ptr, ...) @printf(ptr @.str.3)
  br label %if.end56

if.else55:                                        ; preds = %if.else
  %loadtmp61 = load ptr, ptr %charset, align 8
  %loadtmp62 = load i32, ptr %index, align 4
  %ptradd = getelementptr i8, ptr %loadtmp61, i32 %loadtmp62
  %deref = load i8, ptr %ptradd, align 1
  %promoted = zext i8 %deref to i32
  %calltmp63 = call i32 (ptr, ...) @printf(ptr @.str.4, i32 %promoted)
  br label %if.end56

if.end56:                                         ; preds = %if.else55, %if.then54
  br label %if.end
}

declare i32 @printf(ptr, ...)

declare float @fmodf(float, float)

declare double @fmod(double, double)

declare float @floorf(float)

define double @sqrt_approx(double %x) {
entry:
  %x1 = alloca double, align 8
  store double %x, ptr %x1, align 8
  %loadtmp = load double, ptr %x1, align 8
  %cmptmp = fcmp olt double %loadtmp, 0.000000e+00
  br i1 %cmptmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  ret double -1.000000e+00

if.end:                                           ; preds = %entry
  %loadtmp4 = load double, ptr %x1, align 8
  %cmptmp5 = fcmp oeq double %loadtmp4, 0.000000e+00
  br i1 %cmptmp5, label %if.then2, label %if.end3

if.then2:                                         ; preds = %if.end
  ret double 0.000000e+00

if.end3:                                          ; preds = %if.end
  %loadtmp6 = load double, ptr %x1, align 8
  %fdivtmp = fdiv double %loadtmp6, 2.000000e+00
  %guess = alloca double, align 8
  store double %fdivtmp, ptr %guess, align 8
  %epsilon = alloca double, align 8
  store double 1.000000e-05, ptr %epsilon, align 8
  %i = alloca i32, align 4
  store i32 0, ptr %i, align 4
  br label %while.cond

while.cond:                                       ; preds = %if.end14, %if.end3
  %loadtmp7 = load i32, ptr %i, align 4
  %cmptmp8 = icmp slt i32 %loadtmp7, 20
  br i1 %cmptmp8, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %loadtmp9 = load double, ptr %guess, align 8
  %loadtmp10 = load double, ptr %x1, align 8
  %loadtmp11 = load double, ptr %guess, align 8
  %fdivtmp12 = fdiv double %loadtmp10, %loadtmp11
  %faddtmp = fadd double %loadtmp9, %fdivtmp12
  %fmultmp = fmul double 5.000000e-01, %faddtmp
  %next = alloca double, align 8
  store double %fmultmp, ptr %next, align 8
  %loadtmp15 = load double, ptr %guess, align 8
  %loadtmp16 = load double, ptr %next, align 8
  %fsubtmp = fsub double %loadtmp15, %loadtmp16
  %loadtmp17 = load double, ptr %epsilon, align 8
  %cmptmp18 = fcmp olt double %fsubtmp, %loadtmp17
  %loadtmp19 = load double, ptr %guess, align 8
  %loadtmp20 = load double, ptr %next, align 8
  %fsubtmp21 = fsub double %loadtmp19, %loadtmp20
  %loadtmp22 = load double, ptr %epsilon, align 8
  %fnegtmp = fsub double 0.000000e+00, %loadtmp22
  %cmptmp23 = fcmp ogt double %fsubtmp21, %fnegtmp
  br i1 %cmptmp18, label %and.rhs, label %and.end

while.end:                                        ; preds = %while.cond
  %loadtmp29 = load double, ptr %guess, align 8
  ret double %loadtmp29

if.then13:                                        ; preds = %and.end
  store i32 20, ptr %i, align 4
  %loadtmp24 = load i32, ptr %i, align 4
  br label %if.end14

if.else:                                          ; preds = %and.end
  %loadtmp25 = load double, ptr %next, align 8
  store double %loadtmp25, ptr %guess, align 8
  %loadtmp26 = load double, ptr %guess, align 8
  br label %if.end14

if.end14:                                         ; preds = %if.else, %if.then13
  %loadtmp27 = load i32, ptr %i, align 4
  %addtmp = add i32 %loadtmp27, 1
  store i32 %addtmp, ptr %i, align 4
  %loadtmp28 = load i32, ptr %i, align 4
  %subtmp = sub i32 %loadtmp28, 1
  br label %while.cond

and.rhs:                                          ; preds = %while.body
  br label %and.end

and.end:                                          ; preds = %and.rhs, %while.body
  %andtmp = phi i1 [ %cmptmp18, %while.body ], [ %cmptmp23, %and.rhs ]
  br i1 %andtmp, label %if.then13, label %if.else
}

define double @sdf_sphere(double %px, double %py, double %pz, double %cx, double %cy, double %cz, double %radius) {
entry:
  %px1 = alloca double, align 8
  store double %px, ptr %px1, align 8
  %py2 = alloca double, align 8
  store double %py, ptr %py2, align 8
  %pz3 = alloca double, align 8
  store double %pz, ptr %pz3, align 8
  %cx4 = alloca double, align 8
  store double %cx, ptr %cx4, align 8
  %cy5 = alloca double, align 8
  store double %cy, ptr %cy5, align 8
  %cz6 = alloca double, align 8
  store double %cz, ptr %cz6, align 8
  %radius7 = alloca double, align 8
  store double %radius, ptr %radius7, align 8
  %loadtmp = load double, ptr %px1, align 8
  %loadtmp8 = load double, ptr %cx4, align 8
  %fsubtmp = fsub double %loadtmp, %loadtmp8
  %dx = alloca double, align 8
  store double %fsubtmp, ptr %dx, align 8
  %loadtmp9 = load double, ptr %py2, align 8
  %loadtmp10 = load double, ptr %cy5, align 8
  %fsubtmp11 = fsub double %loadtmp9, %loadtmp10
  %dy = alloca double, align 8
  store double %fsubtmp11, ptr %dy, align 8
  %loadtmp12 = load double, ptr %pz3, align 8
  %loadtmp13 = load double, ptr %cz6, align 8
  %fsubtmp14 = fsub double %loadtmp12, %loadtmp13
  %dz = alloca double, align 8
  store double %fsubtmp14, ptr %dz, align 8
  %loadtmp15 = load double, ptr %dx, align 8
  %loadtmp16 = load double, ptr %dx, align 8
  %fmultmp = fmul double %loadtmp15, %loadtmp16
  %loadtmp17 = load double, ptr %dy, align 8
  %loadtmp18 = load double, ptr %dy, align 8
  %fmultmp19 = fmul double %loadtmp17, %loadtmp18
  %faddtmp = fadd double %fmultmp, %fmultmp19
  %loadtmp20 = load double, ptr %dz, align 8
  %loadtmp21 = load double, ptr %dz, align 8
  %fmultmp22 = fmul double %loadtmp20, %loadtmp21
  %faddtmp23 = fadd double %faddtmp, %fmultmp22
  %calltmp = call double @sqrt_approx(double %faddtmp23)
  %loadtmp24 = load double, ptr %radius7, align 8
  %fsubtmp25 = fsub double %calltmp, %loadtmp24
  ret double %fsubtmp25
}

define double @sdf(double %px, double %py, double %pz) {
entry:
  %px1 = alloca double, align 8
  store double %px, ptr %px1, align 8
  %py2 = alloca double, align 8
  store double %py, ptr %py2, align 8
  %pz3 = alloca double, align 8
  store double %pz, ptr %pz3, align 8
  %spacing = alloca double, align 8
  store double 3.000000e+00, ptr %spacing, align 8
  %loadtmp = load double, ptr %px1, align 8
  %loadtmp4 = load double, ptr %spacing, align 8
  %fmultmp = fmul double %loadtmp4, 5.000000e-01
  %faddtmp = fadd double %loadtmp, %fmultmp
  %loadtmp5 = load double, ptr %spacing, align 8
  %calltmp = call double @fmod(double %faddtmp, double %loadtmp5)
  %rx = alloca double, align 8
  store double %calltmp, ptr %rx, align 8
  %loadtmp6 = load double, ptr %rx, align 8
  %cmptmp = fcmp olt double %loadtmp6, 0.000000e+00
  br i1 %cmptmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %loadtmp7 = load double, ptr %rx, align 8
  %loadtmp8 = load double, ptr %spacing, align 8
  %faddtmp9 = fadd double %loadtmp7, %loadtmp8
  store double %faddtmp9, ptr %rx, align 8
  %loadtmp10 = load double, ptr %rx, align 8
  br label %if.end

if.end:                                           ; preds = %if.then, %entry
  %loadtmp11 = load double, ptr %rx, align 8
  %loadtmp12 = load double, ptr %spacing, align 8
  %fmultmp13 = fmul double %loadtmp12, 5.000000e-01
  %fsubtmp = fsub double %loadtmp11, %fmultmp13
  store double %fsubtmp, ptr %rx, align 8
  %loadtmp14 = load double, ptr %rx, align 8
  %loadtmp15 = load double, ptr %py2, align 8
  %loadtmp16 = load double, ptr %spacing, align 8
  %fmultmp17 = fmul double %loadtmp16, 5.000000e-01
  %faddtmp18 = fadd double %loadtmp15, %fmultmp17
  %loadtmp19 = load double, ptr %spacing, align 8
  %calltmp20 = call double @fmod(double %faddtmp18, double %loadtmp19)
  %ry = alloca double, align 8
  store double %calltmp20, ptr %ry, align 8
  %loadtmp23 = load double, ptr %ry, align 8
  %cmptmp24 = fcmp olt double %loadtmp23, 0.000000e+00
  br i1 %cmptmp24, label %if.then21, label %if.end22

if.then21:                                        ; preds = %if.end
  %loadtmp25 = load double, ptr %ry, align 8
  %loadtmp26 = load double, ptr %spacing, align 8
  %faddtmp27 = fadd double %loadtmp25, %loadtmp26
  store double %faddtmp27, ptr %ry, align 8
  %loadtmp28 = load double, ptr %ry, align 8
  br label %if.end22

if.end22:                                         ; preds = %if.then21, %if.end
  %loadtmp29 = load double, ptr %ry, align 8
  %loadtmp30 = load double, ptr %spacing, align 8
  %fmultmp31 = fmul double %loadtmp30, 5.000000e-01
  %fsubtmp32 = fsub double %loadtmp29, %fmultmp31
  store double %fsubtmp32, ptr %ry, align 8
  %loadtmp33 = load double, ptr %ry, align 8
  %loadtmp34 = load double, ptr %pz3, align 8
  %loadtmp35 = load double, ptr %spacing, align 8
  %fmultmp36 = fmul double %loadtmp35, 5.000000e-01
  %faddtmp37 = fadd double %loadtmp34, %fmultmp36
  %loadtmp38 = load double, ptr %spacing, align 8
  %calltmp39 = call double @fmod(double %faddtmp37, double %loadtmp38)
  %loadtmp40 = load double, ptr %spacing, align 8
  %fmultmp41 = fmul double %loadtmp40, 5.000000e-01
  %fsubtmp42 = fsub double %calltmp39, %fmultmp41
  %rz = alloca double, align 8
  store double %fsubtmp42, ptr %rz, align 8
  %loadtmp43 = load double, ptr %rx, align 8
  %loadtmp44 = load double, ptr %ry, align 8
  %loadtmp45 = load double, ptr %rz, align 8
  %calltmp46 = call double @sdf_sphere(double %loadtmp43, double %loadtmp44, double %loadtmp45, double 0.000000e+00, double 0.000000e+00, double 0.000000e+00, double 1.000000e+00)
  ret double %calltmp46
}

define double @march_ray(double %ox, double %oy, double %oz, double %dx, double %dy, double %dz) {
entry:
  %ox1 = alloca double, align 8
  store double %ox, ptr %ox1, align 8
  %oy2 = alloca double, align 8
  store double %oy, ptr %oy2, align 8
  %oz3 = alloca double, align 8
  store double %oz, ptr %oz3, align 8
  %dx4 = alloca double, align 8
  store double %dx, ptr %dx4, align 8
  %dy5 = alloca double, align 8
  store double %dy, ptr %dy5, align 8
  %dz6 = alloca double, align 8
  store double %dz, ptr %dz6, align 8
  %totalDist = alloca double, align 8
  store double 0.000000e+00, ptr %totalDist, align 8
  %steps = alloca i32, align 4
  store i32 0, ptr %steps, align 4
  br label %while.cond

while.cond:                                       ; preds = %if.end, %entry
  %loadtmp = load i32, ptr %steps, align 4
  %cmptmp = icmp slt i32 %loadtmp, 35
  %loadtmp7 = load double, ptr %totalDist, align 8
  %cmptmp8 = fcmp olt double %loadtmp7, 1.000000e+02
  br i1 %cmptmp, label %and.rhs, label %and.end

while.body:                                       ; preds = %and.end
  %loadtmp9 = load double, ptr %ox1, align 8
  %loadtmp10 = load double, ptr %dx4, align 8
  %loadtmp11 = load double, ptr %totalDist, align 8
  %fmultmp = fmul double %loadtmp10, %loadtmp11
  %faddtmp = fadd double %loadtmp9, %fmultmp
  %px = alloca double, align 8
  store double %faddtmp, ptr %px, align 8
  %loadtmp12 = load double, ptr %oy2, align 8
  %loadtmp13 = load double, ptr %dy5, align 8
  %loadtmp14 = load double, ptr %totalDist, align 8
  %fmultmp15 = fmul double %loadtmp13, %loadtmp14
  %faddtmp16 = fadd double %loadtmp12, %fmultmp15
  %py = alloca double, align 8
  store double %faddtmp16, ptr %py, align 8
  %loadtmp17 = load double, ptr %oz3, align 8
  %loadtmp18 = load double, ptr %dz6, align 8
  %loadtmp19 = load double, ptr %totalDist, align 8
  %fmultmp20 = fmul double %loadtmp18, %loadtmp19
  %faddtmp21 = fadd double %loadtmp17, %fmultmp20
  %pz = alloca double, align 8
  store double %faddtmp21, ptr %pz, align 8
  %loadtmp22 = load double, ptr %px, align 8
  %loadtmp23 = load double, ptr %py, align 8
  %loadtmp24 = load double, ptr %pz, align 8
  %calltmp = call double @sdf(double %loadtmp22, double %loadtmp23, double %loadtmp24)
  %dist = alloca double, align 8
  store double %calltmp, ptr %dist, align 8
  %loadtmp25 = load double, ptr %dist, align 8
  %cmptmp26 = fcmp olt double %loadtmp25, 1.000000e-03
  br i1 %cmptmp26, label %if.then, label %if.end

while.end:                                        ; preds = %and.end
  ret double 0.000000e+00

and.rhs:                                          ; preds = %while.cond
  br label %and.end

and.end:                                          ; preds = %and.rhs, %while.cond
  %andtmp = phi i1 [ %cmptmp, %while.cond ], [ %cmptmp8, %and.rhs ]
  br i1 %andtmp, label %while.body, label %while.end

if.then:                                          ; preds = %while.body
  %loadtmp27 = load double, ptr %totalDist, align 8
  %loadtmp28 = load double, ptr %dist, align 8
  %faddtmp29 = fadd double %loadtmp27, %loadtmp28
  ret double %faddtmp29

if.end:                                           ; preds = %while.body
  %loadtmp30 = load double, ptr %totalDist, align 8
  %loadtmp31 = load double, ptr %dist, align 8
  %faddtmp32 = fadd double %loadtmp30, %loadtmp31
  store double %faddtmp32, ptr %totalDist, align 8
  %loadtmp33 = load double, ptr %totalDist, align 8
  %loadtmp34 = load i32, ptr %steps, align 4
  %addtmp = add i32 %loadtmp34, 1
  store i32 %addtmp, ptr %steps, align 4
  %loadtmp35 = load i32, ptr %steps, align 4
  %subtmp = sub i32 %loadtmp35, 1
  br label %while.cond
}

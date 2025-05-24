; ModuleID = 'global'
source_filename = "global"

@.str.0 = private constant [28 x i8] c"Sqrt 2 is approximately %f\0A\00"

define i32 @main() {
entry:
  %calltmp = call float @sqrt_approx(float 2.000000e+00)
  %promoted = fpext float %calltmp to double
  %calltmp1 = call i32 (ptr, ...) @printf(ptr @.str.0, double %promoted)
  ret i32 0
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

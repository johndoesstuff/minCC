; ModuleID = 'tiny'
source_filename = "tiny"

define i32 @main() {
entry:
  %i = alloca i32, align 4
  %iterations = alloca i32, align 4
  %sign = alloca i32, align 4
  %denom = alloca i32, align 4
  %scale = alloca i32, align 4
  %term = alloca i32, align 4
  %sum = alloca i32, align 4
  %pi_approx = alloca i32, align 4
  store i32 0, ptr %i, align 4
  store i32 1000, ptr %iterations, align 4
  store i32 1, ptr %sign, align 4
  store i32 1, ptr %denom, align 4
  store i32 1000000, ptr %scale, align 4
  store i32 0, ptr %term, align 4
  store i32 0, ptr %sum, align 4
  br label %while.cond

while.cond:                                       ; preds = %if.end, %entry
  %loadtmp = load i32, ptr %i, align 4
  %loadtmp1 = load i32, ptr %iterations, align 4
  %cmptmp = icmp slt i32 %loadtmp, %loadtmp1
  br i1 %cmptmp, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %loadtmp2 = load i32, ptr %scale, align 4
  %loadtmp3 = load i32, ptr %denom, align 4
  %divtmp = sdiv i32 %loadtmp2, %loadtmp3
  store i32 %divtmp, ptr %term, align 4
  %loadtmp4 = load i32, ptr %sign, align 4
  %cmptmp5 = icmp sgt i32 %loadtmp4, 0
  br i1 %cmptmp5, label %if.then, label %if.else

while.end:                                        ; preds = %while.cond
  %loadtmp15 = load i32, ptr %sum, align 4
  %multmp16 = mul i32 4, %loadtmp15
  store i32 %multmp16, ptr %pi_approx, align 4
  %loadtmp17 = load i32, ptr %pi_approx, align 4
  ret i32 %loadtmp17

if.then:                                          ; preds = %while.body
  %loadtmp6 = load i32, ptr %sum, align 4
  %loadtmp7 = load i32, ptr %term, align 4
  %addtmp = add i32 %loadtmp6, %loadtmp7
  store i32 %addtmp, ptr %sum, align 4
  br label %if.end

if.else:                                          ; preds = %while.body
  %loadtmp8 = load i32, ptr %sum, align 4
  %loadtmp9 = load i32, ptr %term, align 4
  %subtmp = sub i32 %loadtmp8, %loadtmp9
  store i32 %subtmp, ptr %sum, align 4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %loadtmp10 = load i32, ptr %sign, align 4
  %multmp = mul i32 %loadtmp10, -1
  store i32 %multmp, ptr %sign, align 4
  %loadtmp11 = load i32, ptr %denom, align 4
  %addtmp12 = add i32 %loadtmp11, 2
  store i32 %addtmp12, ptr %denom, align 4
  %loadtmp13 = load i32, ptr %i, align 4
  %addtmp14 = add i32 %loadtmp13, 1
  store i32 %addtmp14, ptr %i, align 4
  br label %while.cond
}

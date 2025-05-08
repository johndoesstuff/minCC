; ModuleID = 'tiny'
source_filename = "tiny"

define i32 @main() {
entry:
  %target = alloca i32, align 4
  store i32 15, ptr %target, align 4
  %count = alloca i32, align 4
  store i32 0, ptr %count, align 4
  %num = alloca i32, align 4
  store i32 2, ptr %num, align 4
  br label %while.cond

while.cond:                                       ; preds = %if.end11, %entry
  br i1 true, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %i = alloca i32, align 4
  store i32 2, ptr %i, align 4
  %isPrime = alloca i1, align 1
  store i1 true, ptr %isPrime, align 1
  br label %while.cond1

while.end:                                        ; preds = %while.cond
  ret i32 0

while.cond1:                                      ; preds = %if.end, %while.body
  %loadtmp = load i32, ptr %i, align 4
  %loadtmp4 = load i32, ptr %i, align 4
  %multmp = mul i32 %loadtmp, %loadtmp4
  %loadtmp5 = load i32, ptr %num, align 4
  %cmptmp = icmp sle i32 %multmp, %loadtmp5
  br i1 %cmptmp, label %while.body2, label %while.end3

while.body2:                                      ; preds = %while.cond1
  %loadtmp6 = load i32, ptr %num, align 4
  %loadtmp7 = load i32, ptr %i, align 4
  %modtmp = srem i32 %loadtmp6, %loadtmp7
  %cmptmp8 = icmp eq i32 %modtmp, 0
  br i1 %cmptmp8, label %if.then, label %if.end

while.end3:                                       ; preds = %while.cond1
  %loadtmp12 = load i1, ptr %isPrime, align 1
  br i1 %loadtmp12, label %if.then10, label %if.end11

if.then:                                          ; preds = %while.body2
  store i1 false, ptr %isPrime, align 1
  br label %if.end

if.end:                                           ; preds = %if.then, %while.body2
  %loadtmp9 = load i32, ptr %i, align 4
  %addtmp = add i32 %loadtmp9, 1
  store i32 %addtmp, ptr %i, align 4
  br label %while.cond1

if.then10:                                        ; preds = %while.end3
  %loadtmp13 = load i32, ptr %count, align 4
  %addtmp14 = add i32 %loadtmp13, 1
  store i32 %addtmp14, ptr %count, align 4
  %loadtmp17 = load i32, ptr %count, align 4
  %loadtmp18 = load i32, ptr %target, align 4
  %cmptmp19 = icmp eq i32 %loadtmp17, %loadtmp18
  br i1 %cmptmp19, label %if.then15, label %if.end16

if.end11:                                         ; preds = %if.end16, %while.end3
  %loadtmp21 = load i32, ptr %num, align 4
  %addtmp22 = add i32 %loadtmp21, 1
  store i32 %addtmp22, ptr %num, align 4
  br label %while.cond

if.then15:                                        ; preds = %if.then10
  %loadtmp20 = load i32, ptr %num, align 4
  ret i32 %loadtmp20
  br label %if.end16

if.end16:                                         ; preds = %if.then15, %if.then10
  br label %if.end11
}

; ModuleID = 'tiny'
source_filename = "tiny"

define i32 @main() {
entry:
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  %z = alloca i32, align 4
  store i32 1, ptr %x, align 4
  store i32 1, ptr %y, align 4
  store i32 5, ptr %z, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %loadtmp = load i32, ptr %z, align 4
  %cmptmp = icmp sgt i32 %loadtmp, 0
  br i1 %cmptmp, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %loadtmp1 = load i32, ptr %x, align 4
  %loadtmp2 = load i32, ptr %y, align 4
  %addtmp = add i32 %loadtmp1, %loadtmp2
  store i32 %addtmp, ptr %x, align 4
  %loadtmp3 = load i32, ptr %x, align 4
  %loadtmp4 = load i32, ptr %y, align 4
  %addtmp5 = add i32 %loadtmp3, %loadtmp4
  store i32 %addtmp5, ptr %y, align 4
  %loadtmp6 = load i32, ptr %z, align 4
  %subtmp = sub i32 %loadtmp6, 1
  store i32 %subtmp, ptr %z, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %loadtmp7 = load i32, ptr %y, align 4
  ret i32 %loadtmp7
}

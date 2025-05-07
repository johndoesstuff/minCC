; ModuleID = 'tiny'
source_filename = "tiny"

define i32 @main() {
entry:
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  store i32 5, ptr %a, align 4
  %loadtmp = load i32, ptr %a, align 4
  %cmptmp = icmp eq i32 %loadtmp, 5
  br i1 %cmptmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  store i32 3, ptr %b, align 4
  br label %if.end

if.end:                                           ; preds = %if.then, %entry
  %loadtmp1 = load i32, ptr %b, align 4
  ret i32 %loadtmp1
}

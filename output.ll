; ModuleID = 'global'
source_filename = "global"

@.str.0 = private constant [16 x i8] c"Test %d Passed\0A\00"
@.str.1 = private constant [19 x i8] c"!! Test %d Failed\0A\00"
@.str.2 = private constant [24 x i8] c"Running Unit Tests...\0A\0A\00"
@.str.3 = private constant [12 x i8] c"hello world\00"
@.str.4 = private constant [21 x i8] c"\0APassed %d/%d tests\0A\00"

declare i32 @printf(ptr, ...)

declare float @fmodf(float, float)

declare double @fmod(double, double)

declare float @floorf(float)

define void @assert(i1 %condition, ptr %current, ptr %passed) {
entry:
  %condition1 = alloca i1, align 1
  store i1 %condition, ptr %condition1, align 1
  %current2 = alloca ptr, align 8
  store ptr %current, ptr %current2, align 8
  %passed3 = alloca ptr, align 8
  store ptr %passed, ptr %passed3, align 8
  %loadtmp = load i1, ptr %condition1, align 1
  br i1 %loadtmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %loadtmp4 = load ptr, ptr %current2, align 8
  %loadtmp5 = load ptr, ptr %current2, align 8
  %deref = load i32, ptr %loadtmp5, align 4
  %addtmp = add i32 %deref, 1
  store i32 %addtmp, ptr %loadtmp4, align 4
  %subtmp = sub i32 %addtmp, 1
  %loadtmp6 = load ptr, ptr %passed3, align 8
  %loadtmp7 = load ptr, ptr %passed3, align 8
  %deref8 = load i32, ptr %loadtmp7, align 4
  %addtmp9 = add i32 %deref8, 1
  store i32 %addtmp9, ptr %loadtmp6, align 4
  %subtmp10 = sub i32 %addtmp9, 1
  %loadtmp11 = load ptr, ptr %current2, align 8
  %deref12 = load i32, ptr %loadtmp11, align 4
  %calltmp = call i32 (ptr, ...) @printf(ptr @.str.0, i32 %deref12)
  br label %if.end

if.else:                                          ; preds = %entry
  %loadtmp13 = load ptr, ptr %current2, align 8
  %loadtmp14 = load ptr, ptr %current2, align 8
  %deref15 = load i32, ptr %loadtmp14, align 4
  %addtmp16 = add i32 %deref15, 1
  store i32 %addtmp16, ptr %loadtmp13, align 4
  %subtmp17 = sub i32 %addtmp16, 1
  %loadtmp18 = load ptr, ptr %current2, align 8
  %deref19 = load i32, ptr %loadtmp18, align 4
  %calltmp20 = call i32 (ptr, ...) @printf(ptr @.str.1, i32 %deref19)
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void
}

define i32 @square(i32 %x) {
entry:
  %x1 = alloca i32, align 4
  store i32 %x, ptr %x1, align 4
  %loadtmp = load i32, ptr %x1, align 4
  %loadtmp2 = load i32, ptr %x1, align 4
  %multmp = mul i32 %loadtmp, %loadtmp2
  ret i32 %multmp
}

define i32 @main() {
entry:
  %calltmp = call i32 (ptr, ...) @printf(ptr @.str.2)
  %current_test = alloca i32, align 4
  store i32 0, ptr %current_test, align 4
  %tests_passed = alloca i32, align 4
  store i32 0, ptr %tests_passed, align 4
  %a = alloca i32, align 4
  store i32 53, ptr %a, align 4
  %b = alloca i32, align 4
  store i32 21, ptr %b, align 4
  %loadtmp = load i32, ptr %a, align 4
  %cmptmp = icmp eq i32 %loadtmp, 53
  %loadtmp1 = load i32, ptr %current_test, align 4
  %loadtmp2 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp, ptr %current_test, ptr %tests_passed)
  %loadtmp3 = load i32, ptr %a, align 4
  %loadtmp4 = load i32, ptr %b, align 4
  %addtmp = add i32 %loadtmp3, %loadtmp4
  %cmptmp5 = icmp eq i32 %addtmp, 74
  %loadtmp6 = load i32, ptr %current_test, align 4
  %loadtmp7 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp5, ptr %current_test, ptr %tests_passed)
  %loadtmp8 = load i32, ptr %a, align 4
  %loadtmp9 = load i32, ptr %b, align 4
  %subtmp = sub i32 %loadtmp8, %loadtmp9
  %cmptmp10 = icmp eq i32 %subtmp, 32
  %loadtmp11 = load i32, ptr %current_test, align 4
  %loadtmp12 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp10, ptr %current_test, ptr %tests_passed)
  %loadtmp13 = load i32, ptr %a, align 4
  %loadtmp14 = load i32, ptr %b, align 4
  %multmp = mul i32 %loadtmp13, %loadtmp14
  %cmptmp15 = icmp eq i32 %multmp, 1113
  %loadtmp16 = load i32, ptr %current_test, align 4
  %loadtmp17 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp15, ptr %current_test, ptr %tests_passed)
  %loadtmp18 = load i32, ptr %a, align 4
  %loadtmp19 = load i32, ptr %b, align 4
  %divtmp = sdiv i32 %loadtmp18, %loadtmp19
  %cmptmp20 = icmp eq i32 %divtmp, 2
  %loadtmp21 = load i32, ptr %current_test, align 4
  %loadtmp22 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp20, ptr %current_test, ptr %tests_passed)
  %loadtmp23 = load i32, ptr %a, align 4
  %loadtmp24 = load i32, ptr %b, align 4
  %modtmp = srem i32 %loadtmp23, %loadtmp24
  %cmptmp25 = icmp eq i32 %modtmp, 11
  %loadtmp26 = load i32, ptr %current_test, align 4
  %loadtmp27 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp25, ptr %current_test, ptr %tests_passed)
  %loadtmp28 = load i32, ptr %a, align 4
  %deref = load i32, ptr %a, align 4
  %loadtmp29 = load i32, ptr %a, align 4
  %cmptmp30 = icmp eq i32 %deref, %loadtmp29
  %loadtmp31 = load i32, ptr %current_test, align 4
  %loadtmp32 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp30, ptr %current_test, ptr %tests_passed)
  %loadtmp33 = load i32, ptr %a, align 4
  %loadtmp34 = load i32, ptr %b, align 4
  %multmp35 = mul i32 %loadtmp33, %loadtmp34
  %loadtmp36 = load i32, ptr %a, align 4
  %addtmp37 = add i32 %multmp35, %loadtmp36
  %cmptmp38 = icmp eq i32 %addtmp37, 1166
  %loadtmp39 = load i32, ptr %current_test, align 4
  %loadtmp40 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp38, ptr %current_test, ptr %tests_passed)
  %loadtmp41 = load i32, ptr %a, align 4
  %loadtmp42 = load i32, ptr %b, align 4
  %loadtmp43 = load i32, ptr %a, align 4
  %addtmp44 = add i32 %loadtmp42, %loadtmp43
  %multmp45 = mul i32 %loadtmp41, %addtmp44
  %cmptmp46 = icmp eq i32 %multmp45, 3922
  %loadtmp47 = load i32, ptr %current_test, align 4
  %loadtmp48 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp46, ptr %current_test, ptr %tests_passed)
  %str = alloca ptr, align 8
  store ptr @.str.3, ptr %str, align 8
  %loadtmp49 = load ptr, ptr %str, align 8
  %ptradd = getelementptr i8, ptr %loadtmp49, i32 1
  %deref50 = load i8, ptr %ptradd, align 1
  %cmptmp51 = icmp eq i8 %deref50, 101
  %loadtmp52 = load i32, ptr %current_test, align 4
  %loadtmp53 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp51, ptr %current_test, ptr %tests_passed)
  %loadtmp54 = load ptr, ptr %str, align 8
  %ptradd55 = getelementptr i8, ptr %loadtmp54, i32 2
  %deref56 = load i8, ptr %ptradd55, align 1
  %cmptmp57 = icmp eq i8 %deref56, 108
  %loadtmp58 = load i32, ptr %current_test, align 4
  %loadtmp59 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp57, ptr %current_test, ptr %tests_passed)
  %loadtmp60 = load ptr, ptr %str, align 8
  %ptradd61 = getelementptr i8, ptr %loadtmp60, i32 1
  store ptr %ptradd61, ptr %str, align 8
  %ptradd62 = getelementptr i8, ptr %ptradd61, i32 1
  %deref63 = load i8, ptr %ptradd62, align 1
  %cmptmp64 = icmp eq i8 %deref63, 104
  %loadtmp65 = load i32, ptr %current_test, align 4
  %loadtmp66 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp64, ptr %current_test, ptr %tests_passed)
  %loadtmp67 = load ptr, ptr %str, align 8
  %ptradd68 = getelementptr i8, ptr %loadtmp67, i32 1
  store ptr %ptradd68, ptr %str, align 8
  %deref69 = load i8, ptr %ptradd68, align 1
  %cmptmp70 = icmp eq i8 %deref69, 108
  %loadtmp71 = load i32, ptr %current_test, align 4
  %loadtmp72 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp70, ptr %current_test, ptr %tests_passed)
  %x = alloca i32, align 4
  store i32 3, ptr %x, align 4
  %loadtmp73 = load i32, ptr %x, align 4
  %addtmp74 = add i32 %loadtmp73, 1
  store i32 %addtmp74, ptr %x, align 4
  %cmptmp75 = icmp eq i32 %addtmp74, 4
  %loadtmp76 = load i32, ptr %current_test, align 4
  %loadtmp77 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp75, ptr %current_test, ptr %tests_passed)
  %loadtmp78 = load i32, ptr %x, align 4
  %addtmp79 = add i32 %loadtmp78, 1
  store i32 %addtmp79, ptr %x, align 4
  %subtmp80 = sub i32 %addtmp79, 1
  %cmptmp81 = icmp eq i32 %subtmp80, 4
  %loadtmp82 = load i32, ptr %current_test, align 4
  %loadtmp83 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp81, ptr %current_test, ptr %tests_passed)
  %loadtmp84 = load i32, ptr %x, align 4
  %cmptmp85 = icmp eq i32 %loadtmp84, 5
  %loadtmp86 = load i32, ptr %current_test, align 4
  %loadtmp87 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp85, ptr %current_test, ptr %tests_passed)
  %f = alloca float, align 4
  store float 3.000000e+00, ptr %f, align 4
  %loadtmp88 = load float, ptr %f, align 4
  %faddtmp = fadd float %loadtmp88, 0x4007333340000000
  %fptosi = fptosi float %faddtmp to i32
  %i = alloca i32, align 4
  store i32 %fptosi, ptr %i, align 4
  %loadtmp89 = load i32, ptr %i, align 4
  %cmptmp90 = icmp eq i32 %loadtmp89, 5
  %loadtmp91 = load i32, ptr %current_test, align 4
  %loadtmp92 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp90, ptr %current_test, ptr %tests_passed)
  %loadtmp93 = load i32, ptr %a, align 4
  %p = alloca ptr, align 8
  store ptr %a, ptr %p, align 8
  %loadtmp94 = load ptr, ptr %p, align 8
  %deref95 = load i32, ptr %loadtmp94, align 4
  %cmptmp96 = icmp eq i32 %deref95, 53
  %loadtmp97 = load i32, ptr %current_test, align 4
  %loadtmp98 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp96, ptr %current_test, ptr %tests_passed)
  %loadtmp99 = load ptr, ptr %p, align 8
  %ptradd100 = getelementptr i32, ptr %loadtmp99, i32 0
  %deref101 = load i32, ptr %ptradd100, align 4
  %cmptmp102 = icmp eq i32 %deref101, 53
  %loadtmp103 = load i32, ptr %current_test, align 4
  %loadtmp104 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp102, ptr %current_test, ptr %tests_passed)
  %calltmp105 = call i32 @square(i32 4)
  %cmptmp106 = icmp eq i32 %calltmp105, 16
  %loadtmp107 = load i32, ptr %current_test, align 4
  %loadtmp108 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp106, ptr %current_test, ptr %tests_passed)
  %calltmp109 = call i32 @square(i32 6)
  %cmptmp110 = icmp eq i32 %calltmp109, 36
  %loadtmp111 = load i32, ptr %current_test, align 4
  %loadtmp112 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp110, ptr %current_test, ptr %tests_passed)
  %loadtmp113 = load i32, ptr %a, align 4
  %loadtmp114 = load i32, ptr %b, align 4
  %cmptmp115 = icmp sgt i32 %loadtmp113, %loadtmp114
  %cmptmp116 = icmp eq i1 %cmptmp115, true
  %loadtmp117 = load i32, ptr %current_test, align 4
  %loadtmp118 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp116, ptr %current_test, ptr %tests_passed)
  %loadtmp119 = load i32, ptr %a, align 4
  %loadtmp120 = load i32, ptr %b, align 4
  %cmptmp121 = icmp slt i32 %loadtmp119, %loadtmp120
  %cmptmp122 = icmp eq i1 %cmptmp121, false
  %loadtmp123 = load i32, ptr %current_test, align 4
  %loadtmp124 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp122, ptr %current_test, ptr %tests_passed)
  %loadtmp125 = load i32, ptr %a, align 4
  %loadtmp126 = load i32, ptr %b, align 4
  %cmptmp127 = icmp ne i32 %loadtmp125, %loadtmp126
  %cmptmp128 = icmp eq i1 %cmptmp127, true
  %loadtmp129 = load i32, ptr %current_test, align 4
  %loadtmp130 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp128, ptr %current_test, ptr %tests_passed)
  %loadtmp131 = load i32, ptr %a, align 4
  %cmptmp132 = icmp eq i32 %loadtmp131, 53
  %loadtmp133 = load i32, ptr %b, align 4
  %cmptmp134 = icmp eq i32 %loadtmp133, 21
  br i1 %cmptmp132, label %and.rhs, label %and.end

and.rhs:                                          ; preds = %entry
  br label %and.end

and.end:                                          ; preds = %and.rhs, %entry
  %andtmp = phi i1 [ %cmptmp132, %entry ], [ %cmptmp134, %and.rhs ]
  %loadtmp135 = load i32, ptr %current_test, align 4
  %loadtmp136 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %andtmp, ptr %current_test, ptr %tests_passed)
  %loadtmp137 = load i32, ptr %a, align 4
  %cmptmp138 = icmp eq i32 %loadtmp137, 53
  %loadtmp139 = load i32, ptr %b, align 4
  %cmptmp140 = icmp eq i32 %loadtmp139, 0
  br i1 %cmptmp138, label %or.end, label %or.rhs

or.rhs:                                           ; preds = %and.end
  br label %or.end

or.end:                                           ; preds = %or.rhs, %and.end
  %ortmp = phi i1 [ %cmptmp138, %and.end ], [ %cmptmp140, %or.rhs ]
  %loadtmp141 = load i32, ptr %current_test, align 4
  %loadtmp142 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %ortmp, ptr %current_test, ptr %tests_passed)
  %loadtmp143 = load i32, ptr %current_test, align 4
  %loadtmp144 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 true, ptr %current_test, ptr %tests_passed)
  %loadtmp145 = load i32, ptr %current_test, align 4
  %loadtmp146 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 true, ptr %current_test, ptr %tests_passed)
  %loadtmp147 = load i32, ptr %current_test, align 4
  %loadtmp148 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 true, ptr %current_test, ptr %tests_passed)
  %loadtmp149 = load i32, ptr %current_test, align 4
  %loadtmp150 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 true, ptr %current_test, ptr %tests_passed)
  %z = alloca i32, align 4
  store i32 7, ptr %z, align 4
  %loadtmp151 = load i32, ptr %z, align 4
  %q = alloca ptr, align 8
  store ptr %z, ptr %q, align 8
  %loadtmp152 = load ptr, ptr %q, align 8
  %loadtmp153 = load ptr, ptr %q, align 8
  %deref154 = load i32, ptr %loadtmp153, align 4
  %addtmp155 = add i32 %deref154, 5
  store i32 %addtmp155, ptr %loadtmp152, align 4
  %loadtmp156 = load i32, ptr %z, align 4
  %cmptmp157 = icmp eq i32 %loadtmp156, 12
  %loadtmp158 = load i32, ptr %current_test, align 4
  %loadtmp159 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp157, ptr %current_test, ptr %tests_passed)
  %loadtmp160 = load ptr, ptr %q, align 8
  %loadtmp161 = load ptr, ptr %q, align 8
  %deref162 = load i32, ptr %loadtmp161, align 4
  %multmp163 = mul i32 %deref162, 2
  store i32 %multmp163, ptr %loadtmp160, align 4
  %loadtmp164 = load i32, ptr %z, align 4
  %cmptmp165 = icmp eq i32 %loadtmp164, 24
  %loadtmp166 = load i32, ptr %current_test, align 4
  %loadtmp167 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp165, ptr %current_test, ptr %tests_passed)
  %m = alloca i32, align 4
  store i32 5, ptr %m, align 4
  %n = alloca i32, align 4
  store i32 10, ptr %n, align 4
  %loadtmp168 = load i32, ptr %m, align 4
  %loadtmp169 = load i32, ptr %n, align 4
  %addtmp170 = add i32 %loadtmp168, %loadtmp169
  %loadtmp171 = load i32, ptr %n, align 4
  %loadtmp172 = load i32, ptr %m, align 4
  %subtmp173 = sub i32 %loadtmp171, %loadtmp172
  %multmp174 = mul i32 %addtmp170, %subtmp173
  %cmptmp175 = icmp eq i32 %multmp174, 75
  %loadtmp176 = load i32, ptr %current_test, align 4
  %loadtmp177 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp175, ptr %current_test, ptr %tests_passed)
  %loadtmp178 = load i32, ptr %m, align 4
  %addtmp179 = add i32 %loadtmp178, 2
  store i32 %addtmp179, ptr %m, align 4
  %cmptmp180 = icmp eq i32 %addtmp179, 7
  %loadtmp181 = load i32, ptr %current_test, align 4
  %loadtmp182 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp180, ptr %current_test, ptr %tests_passed)
  %check = alloca i32, align 4
  store i32 0, ptr %check, align 4
  %loadtmp183 = load i32, ptr %check, align 4
  %addtmp184 = add i32 %loadtmp183, 1
  store i32 %addtmp184, ptr %check, align 4
  %int_to_bool = icmp ne i32 %addtmp184, 0
  br i1 true, label %or.end186, label %or.rhs185

or.rhs185:                                        ; preds = %or.end
  br label %or.end186

or.end186:                                        ; preds = %or.rhs185, %or.end
  %ortmp187 = phi i1 [ true, %or.end ], [ %int_to_bool, %or.rhs185 ]
  %result = alloca i32, align 4
  %sext = sext i1 %ortmp187 to i32
  store i32 %sext, ptr %result, align 4
  %loadtmp188 = load i32, ptr %check, align 4
  %cmptmp189 = icmp eq i32 %loadtmp188, 0
  %loadtmp190 = load i32, ptr %current_test, align 4
  %loadtmp191 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp189, ptr %current_test, ptr %tests_passed)
  %loadtmp192 = load i32, ptr %result, align 4
  %cmptmp193 = icmp eq i32 %loadtmp192, -1
  %loadtmp194 = load i32, ptr %current_test, align 4
  %loadtmp195 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp193, ptr %current_test, ptr %tests_passed)
  store i32 0, ptr %check, align 4
  %loadtmp196 = load i32, ptr %check, align 4
  %addtmp197 = add i32 %loadtmp196, 1
  store i32 %addtmp197, ptr %check, align 4
  %int_to_bool198 = icmp ne i32 %addtmp197, 0
  br i1 false, label %and.rhs199, label %and.end200

and.rhs199:                                       ; preds = %or.end186
  br label %and.end200

and.end200:                                       ; preds = %and.rhs199, %or.end186
  %andtmp201 = phi i1 [ false, %or.end186 ], [ %int_to_bool198, %and.rhs199 ]
  store i1 %andtmp201, ptr %result, align 1
  %loadtmp202 = load i32, ptr %check, align 4
  %cmptmp203 = icmp eq i32 %loadtmp202, 0
  %loadtmp204 = load i32, ptr %current_test, align 4
  %loadtmp205 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp203, ptr %current_test, ptr %tests_passed)
  %loadtmp206 = load i32, ptr %result, align 4
  %cmptmp207 = icmp eq i32 %loadtmp206, 0
  %loadtmp208 = load i32, ptr %current_test, align 4
  %loadtmp209 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp207, ptr %current_test, ptr %tests_passed)
  store i32 0, ptr %i, align 4
  br i1 true, label %if.then, label %if.end

if.then:                                          ; preds = %and.end200
  store i32 1, ptr %i, align 4
  br label %if.end

if.end:                                           ; preds = %if.then, %and.end200
  %loadtmp210 = load i32, ptr %i, align 4
  %cmptmp211 = icmp eq i32 %loadtmp210, 1
  %loadtmp212 = load i32, ptr %current_test, align 4
  %loadtmp213 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp211, ptr %current_test, ptr %tests_passed)
  br i1 false, label %if.then214, label %if.else

if.then214:                                       ; preds = %if.end
  br label %if.end215

if.else:                                          ; preds = %if.end
  store i32 2, ptr %i, align 4
  br label %if.end215

if.end215:                                        ; preds = %if.else, %if.then214
  %loadtmp216 = load i32, ptr %i, align 4
  %cmptmp217 = icmp eq i32 %loadtmp216, 2
  %loadtmp218 = load i32, ptr %current_test, align 4
  %loadtmp219 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp217, ptr %current_test, ptr %tests_passed)
  br i1 false, label %if.then220, label %if.else221

if.then220:                                       ; preds = %if.end215
  br label %if.end222

if.else221:                                       ; preds = %if.end215
  br i1 true, label %if.then223, label %if.else224

if.end222:                                        ; preds = %if.end225, %if.then220
  %loadtmp226 = load i32, ptr %i, align 4
  %cmptmp227 = icmp eq i32 %loadtmp226, 3
  %loadtmp228 = load i32, ptr %current_test, align 4
  %loadtmp229 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp227, ptr %current_test, ptr %tests_passed)
  br i1 true, label %if.then230, label %if.end231

if.then223:                                       ; preds = %if.else221
  store i32 3, ptr %i, align 4
  br label %if.end225

if.else224:                                       ; preds = %if.else221
  br label %if.end225

if.end225:                                        ; preds = %if.else224, %if.then223
  br label %if.end222

if.then230:                                       ; preds = %if.end222
  br i1 true, label %if.then232, label %if.end233

if.end231:                                        ; preds = %if.end233, %if.end222
  %loadtmp234 = load i32, ptr %i, align 4
  %cmptmp235 = icmp eq i32 %loadtmp234, 4
  %loadtmp236 = load i32, ptr %current_test, align 4
  %loadtmp237 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp235, ptr %current_test, ptr %tests_passed)
  store i32 0, ptr %i, align 4
  %j = alloca i32, align 4
  store i32 0, ptr %j, align 4
  br label %while.cond

if.then232:                                       ; preds = %if.then230
  store i32 4, ptr %i, align 4
  br label %if.end233

if.end233:                                        ; preds = %if.then232, %if.then230
  br label %if.end231

while.cond:                                       ; preds = %while.body, %if.end231
  %loadtmp238 = load i32, ptr %j, align 4
  %cmptmp239 = icmp slt i32 %loadtmp238, 4
  br i1 %cmptmp239, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %loadtmp240 = load i32, ptr %i, align 4
  %addtmp241 = add i32 %loadtmp240, 1
  store i32 %addtmp241, ptr %i, align 4
  %subtmp242 = sub i32 %addtmp241, 1
  %loadtmp243 = load i32, ptr %j, align 4
  %addtmp244 = add i32 %loadtmp243, 1
  store i32 %addtmp244, ptr %j, align 4
  %subtmp245 = sub i32 %addtmp244, 1
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %loadtmp246 = load i32, ptr %i, align 4
  %cmptmp247 = icmp eq i32 %loadtmp246, 4
  %loadtmp248 = load i32, ptr %current_test, align 4
  %loadtmp249 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp247, ptr %current_test, ptr %tests_passed)
  store i32 0, ptr %i, align 4
  %j250 = alloca i32, align 4
  store i32 0, ptr %j250, align 4
  br label %while.cond251

while.cond251:                                    ; preds = %while.end258, %while.end
  %loadtmp254 = load i32, ptr %j250, align 4
  %cmptmp255 = icmp slt i32 %loadtmp254, 4
  br i1 %cmptmp255, label %while.body252, label %while.end253

while.body252:                                    ; preds = %while.cond251
  %k = alloca i32, align 4
  store i32 0, ptr %k, align 4
  br label %while.cond256

while.end253:                                     ; preds = %while.cond251
  %loadtmp270 = load i32, ptr %i, align 4
  %cmptmp271 = icmp eq i32 %loadtmp270, 16
  %loadtmp272 = load i32, ptr %current_test, align 4
  %loadtmp273 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp271, ptr %current_test, ptr %tests_passed)
  store float 4.000000e+00, ptr %f, align 4
  %loadtmp274 = load float, ptr %f, align 4
  %cmptmp275 = fcmp oeq float %loadtmp274, 4.000000e+00
  %loadtmp276 = load i32, ptr %current_test, align 4
  %loadtmp277 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp275, ptr %current_test, ptr %tests_passed)
  %l = alloca i64, align 8
  store i64 67, ptr %l, align 4
  store i32 67, ptr %i, align 4
  %loadtmp278 = load i64, ptr %l, align 4
  %loadtmp279 = load i32, ptr %i, align 4
  %sext280 = sext i32 %loadtmp279 to i64
  %cmptmp281 = icmp eq i64 %loadtmp278, %sext280
  %loadtmp282 = load i32, ptr %current_test, align 4
  %loadtmp283 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp281, ptr %current_test, ptr %tests_passed)
  %loadtmp284 = load i32, ptr %current_test, align 4
  %loadtmp285 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 true, ptr %current_test, ptr %tests_passed)
  %loadtmp286 = load i32, ptr %current_test, align 4
  %loadtmp287 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 true, ptr %current_test, ptr %tests_passed)
  %loadtmp288 = load i32, ptr %current_test, align 4
  %loadtmp289 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 true, ptr %current_test, ptr %tests_passed)
  %loadtmp290 = load i32, ptr %current_test, align 4
  %loadtmp291 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 false, ptr %current_test, ptr %tests_passed)
  %loadtmp292 = load i32, ptr %current_test, align 4
  %loadtmp293 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 false, ptr %current_test, ptr %tests_passed)
  %loadtmp294 = load i32, ptr %current_test, align 4
  %loadtmp295 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 false, ptr %current_test, ptr %tests_passed)
  store i32 2, ptr %i, align 4
  %loadtmp296 = load i32, ptr %i, align 4
  %subtmp297 = sub i32 %loadtmp296, 1
  store i32 %subtmp297, ptr %i, align 4
  %addtmp298 = add i32 %subtmp297, 1
  %cmptmp299 = icmp eq i32 %addtmp298, 2
  %loadtmp300 = load i32, ptr %current_test, align 4
  %loadtmp301 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp299, ptr %current_test, ptr %tests_passed)
  %loadtmp302 = load i32, ptr %i, align 4
  %subtmp303 = sub i32 %loadtmp302, 1
  store i32 %subtmp303, ptr %i, align 4
  %cmptmp304 = icmp eq i32 %subtmp303, 0
  %loadtmp305 = load i32, ptr %current_test, align 4
  %loadtmp306 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp304, ptr %current_test, ptr %tests_passed)
  %s = alloca i16, align 2
  store i16 1, ptr %s, align 2
  %loadtmp307 = load i16, ptr %s, align 2
  %sext308 = sext i16 %loadtmp307 to i32
  %cmptmp309 = icmp eq i32 %sext308, 1
  %loadtmp310 = load i32, ptr %current_test, align 4
  %loadtmp311 = load i32, ptr %tests_passed, align 4
  call void @assert(i1 %cmptmp309, ptr %current_test, ptr %tests_passed)
  %loadtmp312 = load i32, ptr %tests_passed, align 4
  %loadtmp313 = load i32, ptr %current_test, align 4
  %calltmp314 = call i32 (ptr, ...) @printf(ptr @.str.4, i32 %loadtmp312, i32 %loadtmp313)
  ret i32 0

while.cond256:                                    ; preds = %while.body257, %while.body252
  %loadtmp259 = load i32, ptr %k, align 4
  %cmptmp260 = icmp slt i32 %loadtmp259, 4
  br i1 %cmptmp260, label %while.body257, label %while.end258

while.body257:                                    ; preds = %while.cond256
  %loadtmp261 = load i32, ptr %i, align 4
  %addtmp262 = add i32 %loadtmp261, 1
  store i32 %addtmp262, ptr %i, align 4
  %subtmp263 = sub i32 %addtmp262, 1
  %loadtmp264 = load i32, ptr %k, align 4
  %addtmp265 = add i32 %loadtmp264, 1
  store i32 %addtmp265, ptr %k, align 4
  %subtmp266 = sub i32 %addtmp265, 1
  br label %while.cond256

while.end258:                                     ; preds = %while.cond256
  %loadtmp267 = load i32, ptr %j250, align 4
  %addtmp268 = add i32 %loadtmp267, 1
  store i32 %addtmp268, ptr %j250, align 4
  %subtmp269 = sub i32 %addtmp268, 1
  br label %while.cond251
}

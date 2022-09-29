

   .text
   .p2align 4
   .globl keccak256_96
   .type      keccak256_96, @function
keccak256_96:
   {
	 ALLOCFRAME(#0)
   }{
	 r10=#1
	 r11=#31
	 r9=#1536

   }{

	 r6=#4
	 r7=#0
	 m0=r9

   }
   //start
   {
	 v31.b=vsplat(r6)				   //置换高低32位碟形网络参数
	 loop1 (keccaf_loop,#400)
   }
keccaf_loop:

   {
	 v0=vmem(r2++#1):nt
	 r28=r4;
   }

   v5=vmem(r2++#1):nt
   {
	 v10=vmem(r2++#1):nt
	 vmem(r28++#1)=v0
   }{
	 v15=vmem(r2++#1):nt
	 vmem(r28++#1)=v5
   }{
	 v20=vmem(r2++#1):nt
	 vmem(r28++#1)=v10
   }{
	 v1=vmem(r2++#1):nt
	 vmem(r28++#1)=v15
   }{
	 v6=vmem(r2++#1):nt
	 vmem(r28++#1)=v20
   }{
	 v11=vmem(r2++#1):nt
	 vmem(r28++#1)=v1
   }{
	 v16=vmem(r2++#1):nt
	 vmem(r28++#1)=v6
   }{
	 v21=vmem(r2++#1):nt
	 vmem(r28++#1)=v11
   }{
	 v2=vmem(r2++#1):nt
	 vmem(r28++#1)=v16
   }{
	 v7=vmem(r2++#1):nt
	 vmem(r28++#1)=v21
   }{
	 v13=vmem(r1+#2);				   //转置
	 vmem(r28++#1)=v2
   }{
	 vmem(r28++#1)=v7
	 r9=r4;
   }
   v12=vmem(r1):nt
   v8=vmem(r1+#1):nt

   {
	 v17=vsplat(r7)
	 v22=vsplat(r7)
   }{
	 v18=vsplat(r7)

	 v23=vsplat(r7)
   }{
	 v4=vsplat(r7)

	 v9=vsplat(r7)
   }{
	 vtmp.w=vgather(r9,M0,v13.w).w
	 vmem(r28++#1) = vtmp.new
	 r9=add(r9,#8)
   }{
	 vtmp.w=vgather(r9,M0,v13.w).w
	 vmem(r28++#1) = vtmp.new
	 r9=add(r9,#8)
   }{
	 vtmp.w=vgather(r9,M0,v13.w).w
	 vmem(r28++#1) = vtmp.new
	 r9=add(r9,#8)
   }{
	 vtmp.w=vgather(r9,M0,v13.w).w
	 vmem(r28++#1) = vtmp.new
	 r9=add(r9,#8)
   }{
	 vtmp.w=vgather(r9,M0,v13.w).w
	 vmem(r28++#1) = vtmp.new
	 r9=add(r9,#8)
   }{
	 vtmp.w=vgather(r9,M0,v13.w).w
	 vmem(r28++#1) = vtmp.new
	 r9=add(r9,#8)
   }{
	 vtmp.w=vgather(r9,M0,v13.w).w
	 vmem(r28++#1) = vtmp.new
	 r9=add(r9,#8)
   }{
	 vtmp.w=vgather(r9,M0,v13.w).w
	 vmem(r28++#1) = vtmp.new
	 r9=add(r9,#8)
   }{
	 vtmp.w=vgather(r9,M0,v13.w).w
	 vmem(r28++#1) = vtmp.new
	 r9=add(r9,#8)
   }{
	 vtmp.w=vgather(r9,M0,v13.w).w
	 vmem(r28++#1) = vtmp.new
	 r9=add(r9,#8)
   }{
	 vtmp.w=vgather(r9,M0,v13.w).w
	 vmem(r28++#1) = vtmp.new
	 r9=add(r9,#8)
   }{
	 vtmp.w=vgather(r9,M0,v13.w).w
	 vmem(r28++#1) = vtmp.new
	 r9=#1536
   }



   r28=sub(r28,r9)

   v0=vmem(r28++#1):nt
   V5=vmem(r28++#1):nt
   V10=vmem(r28++#1):nt
   V15=vmem(r28++#1):nt
   V20=vmem(r28++#1):nt
   V1=vmem(r28++#1):nt
   V6=vmem(r28++#1):nt
   V11=vmem(r28++#1):nt
   V16=vmem(r28++#1):nt
   V21=vmem(r28++#1):nt
   V2=vmem(r28++#1):nt
   V7=vmem(r28++#1):nt
   {
	 v3=vsplat(r7)
	 v13=vsplat(r7)
   }{
	 v14=vsplat(r7)

	 v19=vsplat(r7)
   }{
	 v24=vsplat(r7)
	 r8=r0
	 loop0 (roundb_loop,#24)
   }
roundb_loop:
   // Theta
   {
	 v25=vxor(v0,v1)
	 v26=vxor(v5,v6)
	 v27=vxor(v10,v11)
	 v30=vxor(v20,v21)
   }{
	 v25=vxor(v25,v2)
	 v26=vxor(v26,v7)
	 v27=vxor(v27,v12)
	 v30=vxor(v30,v22)
   }{
	 v25=vxor(v25,v3)
	 v26=vxor(v26,v8)
	 v27=vxor(v27,v13)
	 v30=vxor(v30,v23)
   }{
	 v25=vxor(v25,v4)				   //行1
	 v26=vxor(v26,v9)				   //行2
	 v27=vxor(v27,v14)				   //行3
	 v30=vxor(v30,v24)				   //行5
   }{
	 v28.w=vasl(v26.w,r10)
	 v29=vrdelta(v26,v31)
   }
   v29.uw=vlsr(v29.uw,r11)
   v28=vor(v28,v29)

   v28=vxor(v30,v28)
   {
	 v0=vxor(v0,v28)
	 v1=vxor(v1,v28)
	 v2=vxor(v2,v28)
   }{
	 v3=vxor(v3,v28)
	 v4=vxor(v4,v28)				   //行1 OK

	 v28.w=vasl(v27.w,r10)
	 v29=vrdelta(v27,v31)
   }
   v29.uw=vlsr(v29.uw,r11)
   v28=vor(v28,v29)
   v28=vxor(v25,v28)
   {
	 v5=vxor(v5,v28)
	 v6=vxor(v6,v28)
	 v7=vxor(v7,v28)
   }{
	 v8=vxor(v8,v28)
	 v9=vxor(v9,v28)				   //行2 OK

	 v28.w=vasl(v25.w,r10)
	 v29=vrdelta(v25,v31)
   }
   v29.uw=vlsr(v29.uw,r11)
   {
	 v28=vor(v28,v29)
	 v25=vxor(v15,v16)
   }

   v25=vxor(v25,v17)
   v25=vxor(v25,v18)
   v25=vxor(v25,v19)


   v28=vxor(v25,v28)

   v20=vxor(v20,v28)
   {
	 v21=vxor(v21,v28)
	 v22=vxor(v22,v28)
	 v23=vxor(v23,v28)
	 v24=vxor(v24,v28)				   //行5 OK
   }{
	 v28.w=vasl(v25.w,r10)
	 v29=vrdelta(v25,v31)
   }
   v29.uw=vlsr(v29.uw,r11)

   v28=vor(v28,v29)

   v28=vxor(v26,v28)
   {
	 v10=vxor(v10,v28)
	 v11=vxor(v11,v28)
	 v12=vxor(v12,v28)
   }{
	 v13=vxor(v13,v28)
	 v14=vxor(v14,v28)				   //行3 OK

	 v28.w=vasl(v30.w,r10)
	 v29=vrdelta(v30,v31)
   }
   v29.uw=vlsr(v29.uw,r11)
   v28=vor(v28,v29)
   v28=vxor(v27,v28)
   {
	 v15=vxor(v15,v28)
	 v16=vxor(v16,v28)
   }{
	 v17=vxor(v17,v28)
	 v18=vxor(v18,v28)
	 v19=vxor(v19,v28)				   //行4OK
   }
   // Rho and pi

   {
	 r12=#3
	 r13=#29
	 r14=#6
	 r15=#26
   }{
	 v25.w=vasl(v5.w,r10)
	 v26=vrdelta(v5,v31)
   }{
	 v27.w=vasl(v2.w,r12)
	 v28=vrdelta(v2,v31)
   }

   v26.uw=vlsr(v26.uw,r11)
   v28.uw=vlsr(v28.uw,r13)

   {
	 v25=vor(v25,v26)				   //1,0
	 v27=vor(v27,v28)				   //0,2

   }{
	 v2=v25
	 v25.w=vasl(v11.w,r14)
	 v26=vrdelta(v11,v31)
   }


   v26.uw=vlsr(v26.uw,r15)

   {
	 v25=vor(v25,v26)				   //2,1
	 v11=v27
   }{
	 r12=#10
	 r13=#22
	 r14=#15
	 r15=#17
   }{
	 v27.w=vasl(v7.w,r12)
	 v28=vrdelta(v7,v31)
   }{
	 v7=v25
	 v25.w=vasl(v13.w,r14)
	 v26=vrdelta(v13,v31)
   }


   v28.uw=vlsr(v28.uw,r13)			   //1,2
   {
	 v27=vor(v27,v28)
	 v26.uw=vlsr(v26.uw,r15)
   }{
	 v25=vor(v25,v26)				   //2,3
	 v13=v27
   }{
	 r12=#21
	 r13=#11
	 r14=#28
	 r15=#4
   }{
	 v27.w=vasl(v18.w,r12)
	 v28=vrdelta(v18,v31)
   }{
	 v18=v25
	 v25.w=vasl(v15.w,r14)
	 v26=vrdelta(v15,v31)
   }
   v28.uw=vlsr(v28.uw,r13)
   {
	 v27=vor(v27,v28)				   //3,3

	 v26.uw=vlsr(v26.uw,r15)		   //3,0
   }{

	 v25=vor(v25,v26)
	 v15=v27
   }{
	 r12=#4
	 r13=#28
	 r14=#13
	 r15=#19
   }{
	 v27.uw=vlsr(v1.uw,r13)
	 v28=vrdelta(v1,v31)
   }{
	 v1=v25
	 v25.uw=vlsr(v8.uw,r15)
	 v26=vrdelta(v8,v31)
   }
   v28.w=vasl(v28.w,r12)			   //0,1
   {

	 v27=vor(v27,v28)


	 v26.w=vasl(v26.w,r14)			   //1,3
   }{
	 v25=vor(v25,v26)
	 v8=v27
   }{
	 r12=#23
	 r13=#9
	 r14=#2
	 r15=#30
   }{
	 v27.uw=vlsr(v16.uw,r13)
	 v28=vrdelta(v16,v31)
   }{
	 v16=v25
	 v25.w=vasl(v9.w,r14)
	 v26=vrdelta(v9,v31)
   }
   v28.w=vasl(v28.w,r12)			   //3,1
   {

	 v27=vor(v27,v28)


	 v26.uw=vlsr(v26.uw,r15)		   //1,4
   }{
	 v25=vor(v25,v26)
	 v9=v27
   }{
	 r12=#14
	 r13=#18
	 r14=#27
	 r15=#5
   }{
	 v27.w=vasl(v24.w,r12)
	 v28=vrdelta(v24,v31)
   }{
	 v24=v25
	 v25.w=vasl(v20.w,r14)
	 v26=vrdelta(v20,v31)
   }
   v28.uw=vlsr(v28.uw,r13)			   //4,4
   {

	 v27=vor(v27,v28)


	 v26.uw=vlsr(v26.uw,r15)		   //4,0
   }{
	 v25=vor(v25,v26)
	 v20=v27
   }{
	 r12=#9
	 r13=#23
	 r14=#24
	 r15=#8
   }{
	 v27.uw=vlsr(v3.uw,r13)
	 v28=vrdelta(v3,v31)
   }{
	 v3=v25
	 v25.uw=vlsr(v19.uw,r15)
	 v26=vrdelta(v19,v31)
   }
   v28.w=vasl(v28.w,r12)			   //0,3
   {

	 v27=vor(v27,v28)


	 v26.w=vasl(v26.w,r14)			   //3,4
   }{
	 v25=vor(v25,v26)
	 v19=v27
   }{
	 r12=#8
	 r13=#24
	 r14=#25
	 r15=#7
   }{
	 v27.w=vasl(v23.w,r12)
	 v28=vrdelta(v23,v31)
   }{
	 v23=v25
	 v25.w=vasl(v17.w,r14)
	 v26=vrdelta(v17,v31)
   }
   v28.uw=vlsr(v28.uw,r13)			   //4,3
   {

	 v27=vor(v27,v28)


	 v26.uw=vlsr(v26.uw,r15)		   //3,2
   }{
	 v25=vor(v25,v26)
	 v17=v27
   }{
	 r12=#11
	 r13=#21
	 r14=#30
	 r15=#2
   }{
	 v27.uw=vlsr(v12.uw,r13)
	 v28=vrdelta(v12,v31)
   }{
	 v12=v25
	 v25.uw=vlsr(v10.uw,r15)
	 v26=vrdelta(v10,v31)
   }
   v28.w=vasl(v28.w,r12)			   //2,2
   {

	 v27=vor(v27,v28)


	 v26.w=vasl(v26.w,r14)			   //2,0
   }{
	 v25=vor(v25,v26)
	 v10=v27
   }{
	 r12=#18
	 r13=#14
	 r14=#7
	 r15=#25
   }{
	 v27.w=vasl(v4.w,r12)
	 v28=vrdelta(v4,v31)
   }{
	 v4=v25
	 v25.uw=vlsr(v22.uw,r15)
	 v26=vrdelta(v22,v31)
   }
   v28.uw=vlsr(v28.uw,r13)			   //0,4
   {

	 v27=vor(v27,v28)



	 v26.w=vasl(v26.w,r14)			   //4,2
   }{
	 v25=vor(v25,v26)
	 v22=v27
   }{
	 r12=#29
	 r13=#3
	 r14=#20
	 r15=#12
   }{
	 v27.uw=vlsr(v14.uw,r13)
	 v28=vrdelta(v14,v31)
   }{
	 v14=v25
	 v25.w=vasl(v21.w,r14)
	 v26=vrdelta(v21,v31)
   }
   v28.w=vasl(v28.w,r12)			   //2,4
   {

	 v27=vor(v27,v28)


	 v26.uw=vlsr(v26.uw,r15)		   //4,1
   }{
	 v25=vor(v25,v26)
	 v21=v27
   }{
	 r12=#12
	 r13=#20
   }{
	 v27.uw=vlsr(v6.uw,r13)
	 v28=vrdelta(v6,v31)
   }
   v28.w=vasl(v28.w,r12)			   //1,1
   v27=vor(v27,v28)
   {


	 v6=v25
	 v5=v27							   //1,0
   }



   // Chi
   {
	 v25=v0
	 v26=v5
	 v27=vnot(v5)
   }{
	 v28=vand(v27,v10)
	 v27=vnot(v10)
   }{
	 v0=vxor(v0,v28)
	 v28=vand(v27,v15)
   }{
	 v5=vxor(v5,v28)
	 v27=vnot(v15)
	 v29=vnot(v20)
   }{
	 v28=vand(v27,v20)
	 v27=vnot(v25)
   }{
	 v10=vxor(v10,v28)
	 v28=vand(v29,v25)
   }{
	 v15=vxor(v15,v28)
	 v30=vand(v27,v26)
   }{
	 v20=vxor(v20,v30)				   //列1

	 v25=v1
	 v26=v6
	 v27=vnot(v6)
   }{
	 v28=vand(v27,v11)
	 v27=vnot(v11)
   }{
	 v1=vxor(v1,v28)
	 v28=vand(v27,v16)
   }{
	 v6=vxor(v6,v28)
	 v27=vnot(v16)
	 v29=vnot(v21)
   }{
	 v28=vand(v27,v21)
	 v27=vnot(v25)
   }{
	 v11=vxor(v11,v28)
	 v28=vand(v29,v25)
   }{
	 v16=vxor(v16,v28)
	 v30=vand(v27,v26)
   }{
	 v21=vxor(v21,v30)				   //列2

	 v25=v2
	 v26=v7
	 v27=vnot(v7)
   }{
	 v28=vand(v27,v12)
	 v27=vnot(v12)
   }{
	 v2=vxor(v2,v28)
	 v28=vand(v27,v17)
   }{
	 v7=vxor(v7,v28)
	 v27=vnot(v17)
	 v29=vnot(v22)
   }{
	 v28=vand(v27,v22)
	 v27=vnot(v25)
   }{
	 v12=vxor(v12,v28)
	 v28=vand(v29,v25)
   }{
	 v17=vxor(v17,v28)
	 v30=vand(v27,v26)
   }{
	 v22=vxor(v22,v30)				   //列3

	 v25=v3
	 v26=v8
	 v27=vnot(v8)
   }{
	 v28=vand(v27,v13)
	 v27=vnot(v13)
   }{
	 v3=vxor(v3,v28)
	 v28=vand(v27,v18)
   }{
	 v8=vxor(v8,v28)
	 v27=vnot(v18)
	 v29=vnot(v23)
   }{
	 v28=vand(v27,v23)
	 v27=vnot(v25)
   }{
	 v13=vxor(v13,v28)
	 v28=vand(v29,v25)
   }{
	 v18=vxor(v18,v28)
	 v30=vand(v27,v26)
   }{
	 v23=vxor(v23,v30)				   //列4

	 v25=v4
	 v26=v9
	 v27=vnot(v9)
   }{
	 v28=vand(v27,v14)
	 v27=vnot(v14)
   }{
	 v4=vxor(v4,v28)
	 v28=vand(v27,v19)
   }{
	 v9=vxor(v9,v28)
	 v27=vnot(v19)
	 v29=vnot(v24)
   }{
	 v28=vand(v27,v24)
	 v27=vnot(v25)

   }{
	 v14=vxor(v14,v28)
	 v28=vand(v29,v25)
	 v25=vmem(r8)					   // Iota
	 r8=add(r8,#128)				   // Iota
   }{
	 v19=vxor(v19,v28)
	 v30=vand(v27,v26)
   }{
	 v24=vxor(v24,v30)				   //列5
	 v0=vxor(v0,v25)				   // Iota
   }:endloop0
   {
	 v16=vmem(r1+#3);				   //转置
	 r28=r4
	 r9=#1536
   }{
	 vscatter(r28,m0,V16.w).w=V0
	 r28=add(r28,#8)
   }{
	 vscatter(r28,m0,V16.w).w=V5
	 r28=add(r28,#8)
   }{
	 vscatter(r28,m0,V16.w).w=V10
	 r28=add(r28,#8)
   }{
	 vscatter(r28,m0,V16.w).w=V15
	 r28=add(r28,#8)
   }
   r28=r4

   vmem(r28+#0):scatter_release
   {
	 vmem(r28+#1):scatter_release
	 v0=vmem(r28++#1):nt
   }{
	 vmem(r28+#1):scatter_release
	 v5=vmem(r28++#1):nt
   }{
	 vmem(r28+#1):scatter_release
	 v10=vmem(r28++#1):nt
   }{
	 v15=vmem(r28++#1):nt
	 vmem(r3++#1):nt=v0
   }
   vmem(r3++#1):nt=v5
   vmem(r3++#1):nt=v10
   {
	 vmem(r3++#1):nt=v15
   }:endloop1

   {
	 DEALLOC_RETURN
   }
   .size      keccak256_96, .-keccak256_96

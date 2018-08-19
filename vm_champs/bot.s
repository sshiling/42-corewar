.name "bot"
.comment "kompot"

load:	st r1, r13
		ld %42991872, r2
		ld %67109122, r3
		ld %-1878917030, r4
		ld %67637312, r5
		ld %218329096, r6
		ld %459632, r7
		ld %1409353736, r9
		ld %107218960, r10
		ld %16, r11
		ld %167766273, r12
		ld %139726864, r14
		ld %269025339, r15

		st r13, 6
		live %0
		fork %:ff2

		ld %-1878851718, r4
		ld %269090651, r15

l1:		ld %16778240, r1
		ld %50297348, r8
		aff r13
f1:		st r8, 7
		st r2, -134
		add r1, r8, r8
		and r8, %268435456, r16
		zjmp %:f1
		live %0
		xor r16, r16, r16
		zjmp %-165

		aff r13
		aff r13
		aff r13
		aff r13
		aff r13
		aff r13
		aff r13
		aff r13
m1:		live %0
		fork %:m2
		fork %:l1
		xor r16, r16, r16
		zjmp %:m1
m2:		live %0
		fork %:l2
ff2:	live %0
		fork %:m1
		live %0

l2:		ld %16778240, r1
		ld %33577476, r8
		aff r13
f2:		st r8, 7
		st r2, 90
		add r1, r8, r8
		and r8, %268435456, r16
		zjmp %:f2
		live %0
		xor r16, r16, r16
		zjmp %59

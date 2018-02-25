/* zfunction.S - zfunction */

/*------------------------------------------------------------------------
 *  zfunction  -  Clearing 10th to 18th bits
 *------------------------------------------------------------------------
 */

	.global	zfunction
zfunction:	pushl	%ebp
		movl	%esp,%ebp
		movl	8(%esp),%eax
		ANDl	$0xffc01fff,%eax
		shl	$4,%eax
		leave
		ret
			


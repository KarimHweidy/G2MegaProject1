#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_



#define EXTI_NUM					23U

#define EXTI_PR_PR0_Pos  			 0U
#define EXTI_PR_PR1_Pos  			 1U
#define EXTI_PR_PR2_Pos  			 2U
#define EXTI_PR_PR3_Pos  			 3U
#define EXTI_PR_PR4_Pos  			 4U
#define EXTI_PR_PR5_Pos  			 5U
#define EXTI_PR_PR6_Pos  			 6U
#define EXTI_PR_PR7_Pos  			 7U
#define EXTI_PR_PR8_Pos  			 8U
#define EXTI_PR_PR9_Pos  			 9U
#define EXTI_PR_PR10_Pos 			10U
#define EXTI_PR_PR11_Pos 			11U
#define EXTI_PR_PR12_Pos 			12U
#define EXTI_PR_PR13_Pos 			13U
#define EXTI_PR_PR14_Pos 			14U
#define EXTI_PR_PR15_Pos 			15U
#define EXTI_PR_PR16_Pos 			16U
#define EXTI_PR_PR17_Pos 			17U
#define EXTI_PR_PR18_Pos 			18U
#define EXTI_PR_PR19_Pos 			19U

#define EXTIX_FLAG(REG,LINE)  ( (REG >> LINE) & 1 )



#endif /* EXTI_PRIVATE_H_ */

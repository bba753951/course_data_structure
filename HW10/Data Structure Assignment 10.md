Data Structure Assignment 10
===
###### tags:`Data Structure`
[TOC]

# Middle-of-Three 方法
1. 令 middle = (left + right) /2
2. 比較 A[left]、A[middle] 與 A[right] 這三筆資料，排出中間值。
3. ==將此中間值再與 A[left] 做交換==
4. 讓現在新的 A[left] 作為 pivot






# 程式結果


- leftmost
	- Longer fisrt:0.004544
	![](https://i.imgur.com/5nFyZmX.png)

	- Shorter first:0.004366
	![](https://i.imgur.com/P4pL4Ad.png)

	- original:0.004323
	![](https://i.imgur.com/2D1mjct.png)

	
 
 
 
- median of three.
	- Longer fisrt:0.004385
	![](https://i.imgur.com/AQwHDy2.png)


	
	- Shorter first：0.004011
	![](https://i.imgur.com/dCVYtbJ.png)


	- original:0.004072
	![](https://i.imgur.com/bvjLshH.png)

## 分析
###  median of three比leftmost好
- 在leftmost
Pivot 恰好是該資料陣列的最小值或最大值，使得切割無法產生一分為二的效果。
造成Worst Case: $O(n^2)$
- Middle-of-Three 方法
如果 pivot 的位置恰好在 n 筆資料中的 n/10 與 9n/10 之間
還是可以收斂到 O( n log n)
### shortest first比較好
應該是因為這樣可以讓比較短的先做完，可以拿掉system stack，給系統更多空間與效率
 
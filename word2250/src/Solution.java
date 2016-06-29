

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;
import java.lang.Math;
import java.lang.reflect.Array;

public class Solution {
	static char[]		Answer;
	static int[][] origin = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
	static int[][] in = new int[4][4];
	static int prevl = -1;
	static int prevGaro = -1;
	static class diff{
		public int diff;
		public int l;
		public int isGaro; //1 garo 2 sero
		public diff(int l, int garo){
			this.l = l;
			this.isGaro = garo;
			
			if(isGaro == 1){
				/*
				diff =  (int) ((Math.pow((origin[l][0]-in[l][0]),2))+
						(Math.pow((origin[l][1]-in[l][1]),2))+
						(Math.pow((origin[l][2]-in[l][2]),2))+
						(Math.pow((origin[l][3]-in[l][3]),2)));
						*/
				for(int i = 0 ; i < 4; i++){
					if(origin[l][i] != in[l][i])
						diff++;
				}
			} else {
				/*
				diff = (int) ((Math.pow((origin[0][l]-in[0][l]),2))+
						(Math.pow((origin[1][l]-in[1][l]),2))+
						(Math.pow((origin[2][l]-in[2][l]),2))+
						(Math.pow((origin[3][l]-in[3][l]),2)));
						*/
				for(int i = 0 ; i < 4; i++){
					if(origin[i][l] != in[i][l])
						diff++;
				}
			}
		}
		public int ifmoved(int n){
			int ret=0;
			if(isGaro == 1){
				/*
				ret = (int) ((Math.pow((origin[l][(0+i)%4]-in[l][(0)]),2))+
						(Math.pow((origin[l][(1+i)%4]-in[l][(1)]),2))+
						(Math.pow((origin[l][(2+i)%4]-in[l][(2)]),2))+
						(Math.pow((origin[l][(3+i)%4]-in[l][(3)]),2)));
						*/
				for(int i = 0 ; i < 4; i++){
					if(origin[l][(i+n)%4] != in[l][i])
						ret++;
				}
			} else {
				/*
				ret = (int) ((Math.pow((origin[(0+i)%4][l]-in[0][l]),2))+
						(Math.pow((origin[(1+i)%4][l]-in[1][l]),2))+
						(Math.pow((origin[(2+i)%4][l]-in[2][l]),2))+
						(Math.pow((origin[(3+i)%4][l]-in[3][l]),2)));
						*/	
				for(int i = 0 ; i < 4; i++){
					if(origin[(i+n)%4][l] != in[i][l])
						ret++;
				}
			}
			return ret;
		}
	}
	public static void main(String[] args)  throws IOException  {
		/*
		아래의 System.setIn 함수는 sample_input.txt 를 read only 형식으로 열어
		표준 입력 스트림으로 redirection 합니다.
		따라서, 키보드를 통한 표준 입력으로 입력 값을 전달하는 대신
		sample_input.txt 파일 내에 존재하는 데이터를 표준 입력 스트림으로 전달합니다.
		본 문제에 대한 소스코드를 테스트함에 있어, 원하는 입력 데이터를 sample_input.txt에 저장하여
		System.setIn 함수를 이용하면, 표준 입력 (키보드 입력) 대신 sample_input.txt 파일의 데이터가 전달됩니다.
		그러므로 테스트를 수행할 때에는 아래의 System.setIn 함수의 주석을 제거하여 사용할 수 있습니다.
		코드를 제출하실 때에는 반드시 System.setIn 함수를 지우거나 주석 처리 해야합니다.
		*/
		System.setIn(new FileInputStream("/home/gg/sample_input_word2250.txt"));

		/*
		표준입력 System.in 으로부터 스캐너를 만들어 데이터를 읽어옵니다.
		*/
		Scanner sc = new Scanner(System.in);
		
		int		T;				// 테스트 케이스의 수
		int		i, l;
		String	tmp;
		String input;
		
		/* 테스트 케이스의 수 T */
		T = sc.nextInt();
		
		
		//ArrayList diffs = new ArrayList<diff>();
		diff diffs[] =  new diff[8];
		/* 각 테스트 케이스에 대한 루프문 */
		for(i = 0; i < T; i++)
		{
			
			for( int n = 0 ; n < 4 ; n ++) {
				for ( int m = 0 ; m < 4; m ++){
					in[n][m] = sc.nextInt(); 
				}
			}
			/*************************************************************************************/
			// 이 곳에 알고리즘을 구현합니다.
			// Input 배열에 저장된 입력 데이터에 대한 정답을 Answer 배열에 저장하는 것을 가정합니다.
			/*************************************************************************************/
			int run = 0;
			for (run = 0;  ; run ++){
			for (int n = 0 ; n < 8; n++){
				int isGaro = n;
				if(isGaro < 4) isGaro = 1; else isGaro = 2;
				diffs[n] = new diff(n%4,isGaro);
			}
			//Collections.sort(diffs,new Comparator<diff>(){
			Arrays.sort(diffs,new Comparator<diff>(){
				@Override
				public int compare(diff o1, diff o2) {
					if (o1.diff < o2.diff){
						return -1;
					} else if(o1.diff > o2.diff){
						return 1;						
					} else {
						return 0;
					}
				}
			});

			
			int min_diff = 999999999;
			int moved = 0;
			if (diffs[7].diff == 0)
				break;
			int max = 7;
			while (moved == 0){
				if (prevl == diffs[max].l && prevGaro == diffs[7].isGaro) {
					max--;
				}
				for( int n = 0 ; n < 4 ; n++) {
					int ret  = diffs[max].ifmoved(n);
					if (min_diff > ret)  {
						min_diff = ret;
						moved = n;
					}
				}
				if(moved==0)
					max--;
			}
			
			prevl = diffs[max].l;
			prevGaro = diffs[max].isGaro;
			
			do_move(diffs[max],moved);
			}
			//System.out.printf("%s\n",input);
			/* 출력부분 */
			//System.out.println("#" + i+1);
			System.out.println(run);
			
			
		}
	}
	private static void do_move(diff diff, int moved) {
		// TODO Auto-generated method stub
		int tmp;
		System.out.println("do_move" + diff.isGaro+" "+(diff.l+1) +" "+ moved);
		if (diff.isGaro == 1) {
			for(int n = 0 ; n < moved ; n++){
				tmp = in[diff.l][3];
	
				in[diff.l][3] = in[diff.l][2];
				in[diff.l][2] = in[diff.l][1];
				in[diff.l][1] = in[diff.l][0];
				in[diff.l][0] = tmp;
			}
		} else {
			for(int n = 0 ; n < moved ; n++){
				tmp = in[3][diff.l];
	
				in[3][diff.l] = in[2][diff.l];
				in[2][diff.l] = in[1][diff.l];
				in[1][diff.l] = in[0][diff.l];
				in[0][diff.l] = tmp;
			}
		}
		
	}
}

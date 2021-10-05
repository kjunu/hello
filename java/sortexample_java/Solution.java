import java.io.FileInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;

public class Solution {
	static class poll{
		int x,y;
		public poll (int x, int y) {
			this.x = x;
			this.y = y;
		}
	}
	public static void main(String[] args)  throws IOException  {
		System.setIn(new FileInputStream("/home/gg/input_AD2.txt"));
		Scanner sc = new Scanner(System.in);
		int		T;
		T = sc.nextInt();
		int total_polls = 0;
		
		poll polls[];
		/* 각 테스트 케이스에 대한 루프문 */
		for(int t = 0; t < T; t++)
		{
			total_polls = sc.nextInt();
			
			polls = new poll[total_polls];
			
			for(int i = 0 ; i < total_polls ; i ++){
				int x = sc.nextInt();
				int y = sc.nextInt();
				polls[i] = new poll(x,y);
			}
			
			Arrays.sort(polls, new Comparator<poll>(){

				@Override
				public int compare(poll o1, poll o2) {
					if (o1.y < o2.y) {
						return 1;
					} else if (o1.y > o2.y) {
						return -1;
					}						
					return 0;
				}
				
			});
			
			poll highest_poll = polls[0];
			
			Arrays.sort(polls, new Comparator<poll>(){

				@Override
				public int compare(poll o1, poll o2) {
					if (o1.x < o2.x) {
						return -1;
					} else if (o1.x > o2.x) {
						return 1;
					}						
					return 0;
				}
				
			});
			
			int max = 0;
			ArrayList<poll> answer = new ArrayList<poll>();
			
			for(int i = 0 ; polls[i].x < highest_poll.x ; i++) {
				if(polls[i].y > max) {
					answer.add(polls[i]);
					max = polls[i].y;
				}					
			}
			answer.add(highest_poll);
			max = 0;
			for(int i = total_polls - 1 ; polls[i].x > highest_poll.x ; i--) {
				if(polls[i].y > max) {
					answer.add(polls[i]);
					max = polls[i].y;
				}					
			}
			
			
			System.out.print ("#" + (t+1) + " ");
			
			for(poll p: answer) {
				System.out.print ("/" + p.x + " " + p.y);
			}
			
			System.out.println();
		}
	}
}

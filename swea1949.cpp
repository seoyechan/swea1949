#include <iostream>
#include <stdio.h>
#include <queue>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int nfiled[9][9];
int nvisit[9][9];
int n, k;
int nRet;
int max_height;
int k_exist;

queue <pair<int, int> > max_height_queue;

const int dirx[] = { 0, 1, 0, -1 }; //위 -> 시계방향
const int diry[] = { -1, 0, 1, 0 };

void dfs(int crtx, int crty, int height)
{
	int nextx = 0;
	int nexty = 0;
	int next_value = 0;
	int crt_value = nfiled[crty][crtx];

	if (max_height < height)
		max_height = height;

	for (int i = 0; i < 4; i++)
	{
		nextx = crtx + dirx[i];
		nexty = crty + diry[i];
		next_value = nfiled[nexty][nextx];

		if (nextx >= 0 && nexty >= 0 && nextx < n && nexty < n && nvisit[nexty][nextx] == 0)
		{
			if (next_value < crt_value) 
			{
				nvisit[nexty][nextx] = 1;
				dfs(nextx, nexty, height + 1);
				nvisit[nexty][nextx] = 0;
			}
			else 
			{
				if (k_exist){ 
					for (int j = 1; j <= k; j++){
						next_value = nfiled[nexty][nextx] - j;
						if (next_value < crt_value){
							k_exist = 0;
							nvisit[nexty][nextx] = 1;
							nfiled[nexty][nextx] = nfiled[nexty][nextx] - j;
							dfs(nextx, nexty, height + 1);
							nfiled[nexty][nextx] = nfiled[nexty][nextx] + j;
							nvisit[nexty][nextx] = 0;
							k_exist = 1;
						}
					}
				}
			}
		}
	}
	
}


int main()
{
	int t;
	int test_case;

	freopen("sample_input.txt","r",stdin);
	scanf("%d", &t);

	for (test_case = 1; test_case <= t; ++test_case)
	{
		scanf("%d %d", &n, &k);
		max_height = 0;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				scanf("%d", &nfiled[i][j]);
				if (max_height < nfiled[i][j])
					max_height = nfiled[i][j];
			}
		}

		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				nvisit[i][j] = 0;
				if (nfiled[i][j] == max_height)
					max_height_queue.push(make_pair(j, i));
			}
		}

		int queue_size = max_height_queue.size();
		max_height = 0;
		for (int i = 0; i < queue_size; i++){
			k_exist = 1;
			nvisit[max_height_queue.front().second][max_height_queue.front().first] = 1;
			dfs(max_height_queue.front().first, max_height_queue.front().second, 0);
			nvisit[max_height_queue.front().second][max_height_queue.front().first] = 0;
			max_height_queue.pop();
		}
		
		nRet = max_height + 1;

		printf("#%d %d\n", test_case, nRet);
	}
	return 0;
}
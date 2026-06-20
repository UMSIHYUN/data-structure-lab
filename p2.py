import sys
from collections import deque

## 입력 받는 코드입니다. 수정할 필요 없습니다.
sys.stdin = open('case.txt')
N, M = list(map(int,input().split()))
print(N, M)
concerts = []
for v in range(N):
    values = list(map(int, input().split()))
    concerts.append(values)

def count_stages(concerts):
    """
    주어진 콘서트장 약도(2차원 배열)에서 연결된 무대 공간('0')의 개수를 세는 함수입니다.

    설계 및 구현 방식:
    - 탐색 알고리즘: DFS(깊이 우선 탐색)를 스택(Stack)을 활용하여 구현했습니다.
    - 2차원 배열의 모든 칸을 순회하며, 아직 방문하지 않은 무대 공간('0')을 발견하면 새로운 무대의 시작점으로 간주합니다.
    - DFS를 통해 해당 지점과 상하좌우로 연결된 모든 무대 공간('0')을 찾아 방문(visited) 처리합니다.
    - DFS 탐색이 한 번 종료될 때마다 독립된 무대 공간 하나를 온전히 찾은 것이므로 개수(answer)를 1 증가시킵니다.
    """
    
    rows = len(concerts)      # 전체 행의 수
    cols = len(concerts[0])   # 전체 열의 수
    
    # 2차원 방문 기록 리스트 초기화 (방문하지 않은 곳은 False)
    is_visited = [[False for _ in range(cols)] for _ in range(rows)]
    
    answer = 0  # 독립적인 무대 공간의 총 개수
    
    # 상, 하, 좌, 우 탐색을 위한 델타값 설정
    dy = [-1, 1, 0, 0] # y축 (행) 이동
    dx = [0, 0, -1, 1] # x축 (열) 이동
    
    # 스택을 활용한 DFS 함수 내부 정의
    def find_connected_stage(start_y, start_x):
        stack = [(start_y, start_x)]
        is_visited[start_y][start_x] = True # 시작 위치 방문 완료 처리
        
        # 스택에 탐색할 칸이 남아있는 동안 반복
        while stack:
            cy, cx = stack.pop()
            
            # 현재 위치(cy, cx)를 기준으로 네 방향 탐색
            for d in range(4):
                ny = cy + dy[d]
                nx = cx + dx[d]
                
                # 다음 탐색할 위치가 약도 영역 내에 있는지 검사
                if 0 <= ny < rows and 0 <= nx < cols:
                    # 펜스가 없는 공간(0)이고, 아직 방문 전이라면
                    if concerts[ny][nx] == 0 and not is_visited[ny][nx]:
                        is_visited[ny][nx] = True # 현재 무대 구역으로 편입 (방문 처리)
                        stack.append((ny, nx))    # 연결된 다음 칸을 계속 탐색하기 위해 스택에 추가
                        
    # 2차원 배열 전체를 순차적으로 확인
    for y in range(rows):
        for x in range(cols):
            # 방문하지 않은 무대 공간(0)을 발견한 경우
            if concerts[y][x] == 0 and not is_visited[y][x]:
                find_connected_stage(y, x) # 인접한 무대 공간을 모두 묶음 처리
                answer += 1                # 새로운 독립 무대를 찾았으므로 카운트 증가
                
    return answer

print(count_stages(concerts))

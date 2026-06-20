from collections import deque

A = {
    0: [1, 2, 3],
    1: [0, 2, 4, 5],
    2: [0, 1, 6],
    3: [0],
    4: [1],
    5: [1],
    6: [2]
}

def bfs(A):
    """
    너비 우선 탐색(BFS)을 수행하는 함수입니다.
    
    인자:
        A (dict): 탐색할 그래프를 나타내는 인접 리스트 형식의 딕셔너리
        
    반환값:
        list: 0번 노드부터 시작해 BFS 알고리즘으로 방문한 노드들의 순서
        
    설명:
        collections 모듈의 deque를 활용하여 큐(Queue) 구조로 구현했습니다.
        시작 노드를 큐에 넣고, 큐에서 노드를 하나씩 빼면서 인접한 노드 중 
        아직 방문하지 않은 노드를 다시 큐에 추가하는 방식으로 동작합니다.
        딕셔너리의 리스트가 이미 오름차순 정렬되어 있어 번호가 빠른 노드부터 탐색됩니다.
    """
    
    answer = []                  # 방문 순서를 저장할 리스트
    visited_nodes = {0}          # 시작 노드 0 방문 처리
    queue = deque([0])           # BFS 탐색용 큐 초기화
    
    # 큐가 빌 때까지 반복
    while queue:
        current = queue.popleft()   # 큐의 맨 앞 노드 꺼내기
        answer.append(current)      # 방문 순서 기록
        
        # 현재 노드와 연결된 인접 노드 확인
        for next_node in A[current]:
            
            # 아직 방문하지 않은 노드라면
            if next_node not in visited_nodes:
                visited_nodes.add(next_node)   # 방문 처리
                queue.append(next_node)        # 큐에 추가
                
    return answer

def dfs(A):
    """
    깊이 우선 탐색(DFS)을 수행하는 함수입니다.
    
    인자:
        A (dict): 탐색할 그래프를 나타내는 인접 리스트 형식의 딕셔너리
        
    반환값:
        list: 0번 노드부터 시작해 DFS 알고리즘으로 방문한 노드들의 순서
        
    설명:
        파이썬의 리스트를 스택(Stack)처럼 활용하여 구현했습니다.
        문제의 조건에 따라 같은 레벨에서는 번호가 작은 노드를 먼저 방문해야 합니다.
        스택은 LIFO(후입선출) 구조이므로, 인접 노드를 reversed()로 뒤집어서 
        스택에 넣어야 번호가 작은 노드가 스택의 맨 위에 위치하여 먼저 꺼내집니다.
    """
    
    answer = []                  # 방문 순서를 저장할 리스트
    visited_nodes = {0}          # 시작 노드 0 방문 처리
    stack = [0]                  # DFS 탐색용 스택 초기화
    
    # 스택이 빌 때까지 반복
    while stack:
        current = stack.pop()    # 스택의 맨 위 노드 꺼내기
        answer.append(current)   # 방문 순서 기록
        
        # 번호가 작은 노드를 먼저 방문하기 위해 reversed 사용
        for next_node in reversed(A[current]):
            
            # 아직 방문하지 않은 노드라면
            if next_node not in visited_nodes:
                visited_nodes.add(next_node)   # 방문 처리
                stack.append(next_node)        # 스택에 추가
                
    return answer

# 아래는 체크함수입니다. 수정하실 필요 없습니다.
bfs_result = bfs(A)
dfs_result = dfs(A)

assert bfs_result == [0,1,2,3,4,5,6]
assert dfs_result == [0,1,4,5,2,6,3]

print('PASSED!')

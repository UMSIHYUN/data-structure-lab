# ==========================================
# 1. 버블 정렬 (Bubble Sort)
# ==========================================
def bubble_sort(a_list):
    for pass_num in range(len(a_list) - 1, 0, -1):
        for i in range(pass_num):
            if a_list[i] > a_list[i + 1]:
                temp = a_list[i]
                a_list[i] = a_list[i + 1]
                a_list[i + 1] = temp

# ==========================================
# 2. 선택 정렬 (Selection Sort)
# ==========================================
def selection_sort(a_list):
    for fill_slot in range(len(a_list) - 1, 0, -1):
        pos_of_max = 0
        for location in range(1, fill_slot + 1):
            if a_list[location] > a_list[pos_of_max]:
                pos_of_max = location
                
        temp = a_list[fill_slot]
        a_list[fill_slot] = a_list[pos_of_max]
        a_list[pos_of_max] = temp

# ==========================================
# 3. 삽입 정렬 (Insertion Sort)
# ==========================================
def insertion_sort(a_list):
    for index in range(1, len(a_list)):
        current_value = a_list[index]
        position = index
        
        while position > 0 and a_list[position - 1] > current_value:
            a_list[position] = a_list[position - 1]
            position = position - 1
            
        a_list[position] = current_value

# ==========================================
# 4. 쉘 정렬 (Shell Sort)
# ==========================================
def shell_sort(a_list):
    sublist_count = len(a_list) // 2
    while sublist_count > 0:
        for start_position in range(sublist_count):
            gap_insertion_sort(a_list, start_position, sublist_count)
        sublist_count = sublist_count // 2

def gap_insertion_sort(a_list, start, gap):
    for i in range(start + gap, len(a_list), gap):
        current_value = a_list[i]
        position = i
        
        while position >= gap and a_list[position - gap] > current_value:
            a_list[position] = a_list[position - gap]
            position = position - gap
            
        a_list[position] = current_value

# ==========================================
# 5. 병합 정렬 (Merge Sort)
# ==========================================
def merge_sort(a_list):
    if len(a_list) > 1:
        mid = len(a_list) // 2
        left_half = a_list[:mid]
        right_half = a_list[mid:]
        
        merge_sort(left_half)
        merge_sort(right_half)
        
        i = 0
        j = 0
        k = 0
        
        while i < len(left_half) and j < len(right_half):
            if left_half[i] < right_half[j]:
                a_list[k] = left_half[i]
                i = i + 1
            else:
                a_list[k] = right_half[j]
                j = j + 1
            k = k + 1
            
        while i < len(left_half):
            a_list[k] = left_half[i]
            i = i + 1
            k = k + 1
            
        while j < len(right_half):
            a_list[k] = right_half[j]
            j = j + 1
            k = k + 1

# ==========================================
# 6. 퀵 정렬 (Quick Sort)
# ==========================================
def quick_sort(a_list):
    quick_sort_helper(a_list, 0, len(a_list) - 1)

def quick_sort_helper(a_list, first, last):
    if first < last:
        split_point = partition(a_list, first, last)
        quick_sort_helper(a_list, first, split_point - 1)
        quick_sort_helper(a_list, split_point + 1, last)

def partition(a_list, first, last):
    pivot_value = a_list[first]
    left_mark = first + 1
    right_mark = last
    done = False
    
    while not done:
        while left_mark <= right_mark and a_list[left_mark] <= pivot_value:
            left_mark = left_mark + 1
        while a_list[right_mark] >= pivot_value and right_mark >= left_mark:
            right_mark = right_mark - 1
            
        if right_mark < left_mark:
            done = True
        else:
            temp = a_list[left_mark]
            a_list[left_mark] = a_list[right_mark]
            a_list[right_mark] = temp
            
    temp = a_list[first]
    a_list[first] = a_list[right_mark]
    a_list[right_mark] = temp
    
    return right_mark


# ==========================================
# 7. 여기서부터 실제 실행 및 테스트 코드!
# ==========================================
if __name__ == "__main__":
    # 정렬되지 않은 임의의 리스트 생성
    data = [26, 93, 17, 77, 31, 44, 55, 20, 99, 1]
    print("원래 데이터:", data)
    
    # 예시로 '버블 정렬' 실행해보기
    # (다른 정렬을 테스트하고 싶다면 bubble_sort 대신 quick_sort(data) 등으로 바꾸면 됩니다)
    bubble_sort(data)
    
    print("정렬 후 데이터:", data)

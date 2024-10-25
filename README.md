`Cây AVL là cây cân bằng, tính chất này duy trì mọi thời điểm`

**Xét cây AVL có n nút, độ cao h**: 
Các thao tác xây dựng:
  Thêm một nút vào cây - cân bằng lại
  Xoá một nút khỏi cây - cân bằng lại
  In các nút trên cây theo độ cao, từ trái sang phải (độ cao 0 -> h-1)


Breakdown code: 
`
class Node{
a
    public:
        int value;
        Node* left;
        Node* right;
        int height;
        Node(int data){
            this->value = data;
            left = NULL;
            right = NULL;
            height = 1;
        }
};
`

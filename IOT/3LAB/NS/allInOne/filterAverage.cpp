
float smooth(int input[], int size, int window)
{

  // do weights
  int* weights = new int[size]; 
  int count = 0;

  for(int i = 0; i < size; i++){
    int t = input[i];
    for(int j = 0; j < size; j++){
      if(t == input[j]) count++;
    }
    weights[i] = count;
    count = 0;
  }

  int top = 0, bottom = 0;

  for(int j = 0; j < size; j++){
    top += weights[j] * input[j];
    bottom += weights[j];
  }

  return top/bottom;

}
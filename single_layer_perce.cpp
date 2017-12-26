#include <iostream>
#include <vector>
#include <random>

using namespace std;

// defining an object called perceptron
class perceptron
{
  private:
    vector<float> weights;
    vector<int> inputs;

    int size_;//number of inputs for the perceptron or node
    int output;

    float l_rate;
    float error;

  public:
    perceptron(){} //default constructor
    virtual ~perceptron(){}//destructor
    perceptron(int size): weights(size,0) // initialises the weights
    {
      size_ = size;
      l_rate = 0.01;

      default_random_engine generator(rand());
      uniform_real_distribution<float> wei(0,1);

      for(int i = 0; i < (size); i++)
      {
        weights.at(i) = wei(generator);
      }

    }

    void setup_ins(vector<int> &ins)//sets up inputs
    {
      inputs = ins;
    }

    int activation() //this is a step activation function determines whether
    {               // whether 0 or 1
      float sum = 0;
      for(int i = 0; i < inputs.size(); i++)
      {
        sum += (inputs.at(i) * weights.at(i+1));
      }
      sum += 1 * weights.at(0); // 1 is bias
      if(sum  > 0.7)
      {
        output = 1;
      }
      else
      {
        output = 0;
      }
      return output;
    }

    void error_eval(int i) // finds difference in errors
    {
      error = i - output;
    }

    void backpropagation() //backpropagates the weights value
    {
        for(int i = 0; i < size_; i++)
        {
            if(i == 0)
            {
              weights.at(i) += l_rate*1*error;
            }
            else
            {
              weights.at(i) += l_rate*inputs.at(i-1)*error;
            }
        }
    }
};

int main()
{
  vector<vector<int>> ins = {{0,0},{0,1},{1,0},{1,1}};
  vector<int> outs = {0,0,0,1};
  perceptron * p_node = new perceptron(3);//size of the weights plus for bias

  for(int i = 0; i < 100; i++)
  {
    cout << "iteration " << i << endl;
    for(int j = 0; j < 4; j++)
    {
      p_node->setup_ins(ins.at(j)); // needs inputs in turn by turn
      p_node->activation();
      if(p_node->activation() == outs.at(j))
      {
        cout << "correct prediction" << endl;
      }
      p_node->error_eval(outs.at(j));
      p_node->backpropagation();
    }
  }
  // to test whether the perceptron learnt or not
  int a,b;
  cout << "please enter two binary number seperately" << endl;
  cin >> a;
  cout << "enter second value" << endl;
  cin >> b;
  vector<int> inps = {a,b};
  p_node->setup_ins(inps);
  cout << p_node->activation() << " is your answer" << endl;

  return 0;
}

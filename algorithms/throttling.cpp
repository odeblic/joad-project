// absolute max number of messages per period
int max;

// required average number of messages per period
std::deque<int> window;

int get_sum()
{
  int sum = 0;
  for(i : window)
  {
    sum += i;
  }
  return sum;
}

int get_actual_allowed_number(int n)
{
  if(n > max)
  {
    return max;
  }
  else if(n > get_sum())
  {
    return get_sum();
  }
  else
  {
    return n;
  }
}


/////////////////////////////////////////////////


class Manager
{
  float credit; // nb of msg allowed altogether at current time
  float maxThroughput;
  std::queue waitingMsg;
  current_time;

  class WaitingChannel
  {
    const Channel& channel;
    const short remaining_time;
    const short priority;
  };

  void loop()
  {
    // TODO adjust current_time every cycle to avoid a syscall at each iteration

    const float period;

    sleep(period);
    // wait_for(current_time + period);

    credit += maxThroughput * period;

    for(channel : list)
    {
      if(channel.trigger(current_time) <= 0)
      {
        waitingMsg.push(channel); // a priority queue would make sure that the most urgent msg will be sent first
      }
    }

    while(waitingMsg.size() > 0 && credit > 0)
    {
      send(waitingMsg.pop());
      credit--;
    }
  }
};


class Channel
{
  float period; // frequency
  short priority;
  float timestamp; // last message sent

  float trigger(float current_time)
  {
    remaining_time = current_time - timestamp;

    return remaining_time;
  }
};


int main(int argc, char ** argv)
{


}

/*
Process processing Units

Throughput = Processed Units Count / Processing Time

Latency = Processing Time
*/

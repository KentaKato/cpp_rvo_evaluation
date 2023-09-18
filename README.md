# cpp_rvo_evaluation

# 概要
C++17で関数から値を返す手段によって、処理時間の差があるか実験

# 評価結果

| 方式 | 所要時間 [ms] |
| ---- | ---- |
| 値返し（RVO） | 15,448 |
| 出力引数（参照渡し） | 15,304 |
| std::move | 15,301 |

⇒ 今回の評価環境においては差はなし。RVOに期待し、値返しで定義しまってよさそう。

# 評価条件

下記関数をそれぞれ100,000回ずつ実行し、所要時間を計測

```cpp

// 値返し (RVOに頼る)
std::vector<std::string> return_value()
{
    return std::vector<std::string>(10'000, "test");
}

// 出力引数 (参照)
void output_argument(std::vector<std::string> &v)
{
    v = std::vector<std::string>(10'000, "test");
}

// move
std::vector<std::string> return_move()
{
    std::vector<std::string> v(10'000, "test");
    return std::move(v);
}

```

# ビルド＆実行
1. Create a build directory:

   ```bash
   mkdir build
   cd build
   ```

1. Run CMake and build:

   ```bash
   cmake ..
   make
   ```

This will produce the executable file `main` in the `build` directory.

1. Execute:

    ```bash
    ./main
    ```
import numpy as np
import pandas as pd

from gensim import corpora
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from nltk.stem import SnowballStemmer

from keras.preprocessing import sequence
from keras.utils import np_utils
from keras.models import Sequential
from keras.layers import Dense, Dropout, Activation, Embedding, pooling, convolutional
from keras.layers import LSTM, GRU
from keras.models import Model

np.random.seed(0)

if __name__ == "__main__":

    # 读入训练集和测试集
    print("读入数据")
    train_df = pd.read_csv('train.tsv', header=0, delimiter='\t')
    test_df = pd.read_csv('test.tsv', header=0, delimiter='\t')

    #PhraseId	SentenceId	Phrase Sentiment
    row_Phrase_train = train_df['Phrase'].values
    row_Phrase_test = test_df['Phrase'].values
    row_Sentiment_train = train_df['Sentiment'].values
    Senti_variety = len(np.unique(row_Sentiment_train))
    #print("Variety of Label: ", Senti_variety)

    #分词
    print("分词、过滤、词干化")
    stop_words = set(stopwords.words('english'))
    symbols = ['.', ',', '"', '\'', ':', ';', '(', ')', '[', ']', '{', '}']
    stop_words.update(symbols)
    #print("stopwords:  ", stop_words)
    #英语词干处理
    Snow_Stem = SnowballStemmer('english')

    train_words = []
    for row in row_Phrase_train:
        tokens = word_tokenize(row)
        filtered = [word for word in tokens if word not in stop_words]
        #print("after tokenize:  ", filtered)
        #找到对应词干
        stemmed = [Snow_Stem.stem(word) for word in filtered]
        #print("after stem:  ", stemmed)
        train_words.append(stemmed)

    test_words = []
    for row in row_Phrase_test:
        tokens = word_tokenize(row)
        filtered = [word for word in tokens if word not in stop_words]
        stemmed = [Snow_Stem.stem(word) for word in filtered]
        test_words.append(stemmed)

    all_words = np.concatenate((train_words, test_words), axis=0)

    #建立词典
    print("建立词典")
    dictionary = corpora.Dictionary(all_words)
    dictionary_size = len(dictionary.keys())
    print("dictionary size: ", dictionary_size)
    print("dictionary： ", dictionary.token2id)

    #序列化
    print ("序列化")
    train_seq, word_id_len = [], []
    for row in train_words:
        word_ids = [dictionary.token2id[word] for word in row]
        train_seq.append(word_ids)
        word_id_len.append(len(word_ids))
    print(len(train_seq))
    test_seq, word_ids = [], []
    for row in test_words:
        word_ids = [dictionary.token2id[word] for word in row]
        test_seq.append(word_ids)
        word_id_len.append(len(word_ids))

    vector_len = int(np.round((2 * np.mean(word_id_len) + 2 * np.std(word_id_len))))
    #长为16的向量
    print(vector_len)

    #向量化
    print("向量化")
    train_vector = sequence.pad_sequences(np.array(train_seq), maxlen=vector_len, value=0)
    print("matrix shape:  ", train_vector.shape)
    print(train_vector[0])
    print(train_vector[1])
    print(train_vector[2])
    test_vector = sequence.pad_sequences(np.array(test_seq), maxlen=vector_len)
    y_train_enc = np_utils.to_categorical(row_Sentiment_train, Senti_variety)


    print("fitting LSTM ...")
    model = Sequential()
    #嵌入层，转离散值向量为实数向量
    model.add(Embedding(dictionary_size, 256, name='embd'))
    #循环层LSTM
    #model.add(LSTM(256, implementation=2))
    #GRU
    model.add(GRU(256, name='gru'))
    model.add(Activation('relu'))
    #全连接层1
    model.add(Dense(128))
    model.add(Dropout(0.15))
    model.add(Activation('relu'))
    #全连接层2，用于分类输出
    model.add(Dense(Senti_variety)) #5种label
    model.add(Activation('softmax'))

    model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])
    model.fit(train_vector, y_train_enc, epochs=1, batch_size=256, verbose=1)

    predict = model.predict_classes(test_vector)

    #写入csv文件
    test_df['Sentiment'] = predict.reshape(-1, 1)
    header = ['PhraseId', 'Sentiment']
    test_df.to_csv('predict.csv', columns=header, index=False, header=True)

    #使用函数式模型api获得Embedding层输出
    embd = Model(inputs=model.input,
                 outputs=model.get_layer('embd').output)
    # 以这个model的预测值作为输出
    embd_output = embd.predict(train_vector)
    print('Embedding output shape:  ', embd_output.shape)
    print(embd_output[0].shape)
    print("after embedding:  ", embd_output)
    #GRU层输出
    gru = Model(inputs=model.input,
                outputs=model.get_layer('gru').output)
    gru_output = gru.predict(train_vector)
    print('GRU output shape:  ', gru_output.shape)
    print("after GRU:  ", gru_output)

all: wordcount

wordcount: WordCount.java
	javac -classpath /usr/local/hadoop/hadoop-0.20.2-core.jar \
			-d wordcount_classes/ WordCount.java
	jar -cvf wordcount.jar -C wordcount_classes/ .

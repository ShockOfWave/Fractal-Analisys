FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        build-essential \
        software-properties-common \
        python3.10 \
        python3-pip \
        python3-apt \
        cmake \
        make \
        libgsl-dev && \
    apt-get clean

ENV LC_ALL en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US.UTF-8

WORKDIR /app

COPY . .

RUN pip install .

EXPOSE 8512

HEALTHCHECK CMD curl --fail http://localhost:8501/_stcode/health

ENTRYPOINT ["streamlit", "run", "app.py"]

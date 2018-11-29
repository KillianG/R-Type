FROM debian

RUN apt-get update && apt-get install -y git \
			cmake \
			g++ \
			gcovr \
			build-essential \
			libpthread-stubs0-dev \
			libgl1-mesa-dev \
			libx11-dev \
			libxrandr-dev \
			libfreetype6-dev \
			libglew-dev \
			libjpeg-dev \
			libsndfile1-dev \
			libopenal-dev \
			libudev-dev \
			libnet1-dev \
			libboost-all-dev \
			libsfml-dev


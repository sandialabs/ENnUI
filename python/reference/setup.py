import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()
setuptools.setup(
    name="pure_ennui",
    version="0.0.1",
    author="Mike Walker",
    author_email="mrwalke@sandia.gov",
    description="Pure-python ENnUI",
    long_description=long_description,
    long_description_content_type="text/markdown",
    packages=setuptools.find_packages(),
)

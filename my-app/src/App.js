import logo from './logo.svg';
import './App.css';
import { useState } from 'react';
import { Box, Button, Grid, Input, ListItem, UnorderedList } from '@chakra-ui/react';

function App() {

  const [fileInput, setFileInput] = useState(null);
  const [previewImage, setPreviewImage] = useState("https://i1.wp.com/stargazersworld.com/wordpress/wp-content/uploads/2016/08/mystery-person-silhouette.png?fit=228%2C221&ssl=1");
  const [isLoading, setIsLoading] = useState(false);
  const [imageUrl, setImageUrl] = useState("https://i1.wp.com/stargazersworld.com/wordpress/wp-content/uploads/2016/08/mystery-person-silhouette.png?fit=228%2C221&ssl=1");
  const [results, setResults] = useState([])

  const [sizeResult, setSizeResult]  = useState(1);

  const fileChange = event => {
    setFileInput(event.target.files[0]);
    setPreviewImage(URL.createObjectURL(event.target.files[0]));
    console.log(previewImage)
  }


  const sizeChange = event => {
    setSizeResult(event.target.value)
    console.log(event.target.value)
  }

  const getPhoto = (index) => {
    const formData = new FormData();
    formData.append(
      "path", results[index]
    )

    console.log(results[index])
    fetch('http://127.0.0.1:5000/get-photo', {
      method: 'POST',
      body: formData
    }).then(
      async response => {
        var responseBlob = await response.blob();
        console.log(responseBlob)
        console.log(URL.createObjectURL(responseBlob))
        setImageUrl(URL.createObjectURL(responseBlob))
      }
    ).then(
      success => setIsLoading(false)
    ).catch(
      error => {
        console.log(error) // Handle the error response object
        setIsLoading(false)
      }
    )
  }

  const sendFile = () => {
    setIsLoading(true)
    const formData = new FormData();
    formData.append(
      "image",
      fileInput,
      fileInput.name
    );

      formData.append('k', sizeResult)

    fetch('http://127.0.0.1:5000/', {
      method: 'POST',
      body: formData
    }).then(
      async response => {
        var data = await response.json()
        console.log(data['results'])
        setResults(data['results'])
        /*var responseBlob = await response.blob();
        console.log(responseBlob)
        setImageUrl(URL.createObjectURL(responseBlob))*/
      }
    ).then(
      success => {
        setIsLoading(false)
      }
    ).catch(
      error => {
        console.log(error) // Handle the error response object
        setIsLoading(false)
      }
    )
  }

  return (
    <div className="App">
      <header className="App-header">
        <Grid templateColumns="repeat(2, 1fr)" gap={6}>
          <Box>
            <div>Sube la cara de la persona que buscas</div>
            <input type="file" onChange={fileChange}/>
            <img src={previewImage} width="240px" />
          </Box>
          <Box display="flex">
            <Box>
              <Input placeholder="Enter number of results" size="lg"  onChange={sizeChange}/>
              <Button variant="outline" onClick={sendFile}>Find similar faces</Button>
              <UnorderedList>
                {
                  results && 
                    results.map( (item, count) => <ListItem _hover={{cursor:"pointer", color: 'green'}} onClick={() => getPhoto(count)} id={count} >{item}</ListItem>)
                }
              </UnorderedList>
            </Box>
            <Box>


            
              {
                isLoading ? 
                <img src={logo} className="App-logo" alt="logo" />
                : 
                <img src={imageUrl} />
              }

          </Box>
          </Box>
        </Grid>
        
      </header>
    </div>
  );
}

export default App;

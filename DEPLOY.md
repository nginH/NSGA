# Deploying NSGA Visualization to Vercel

This guide explains how to deploy the NSGA visualization to Vercel.

## Prerequisites

1. A [Vercel](https://vercel.com) account
2. The [Vercel CLI](https://vercel.com/docs/cli) (optional)

## Files for Deployment

Ensure these files are in your project directory:
- `nsga_visualization.html` - The main visualization file
- `vercel.json` - Vercel configuration
- `index.html` - Fallback redirect page

## Deployment Steps

### Option 1: Deploy via Vercel Dashboard

1. Log in to your Vercel account
2. Create a new project
3. Import your project repository from GitHub, GitLab, or Bitbucket, or upload your files
4. Vercel will automatically detect the configuration and deploy the site

### Option 2: Deploy via Vercel CLI

1. Install Vercel CLI: `npm i -g vercel`
2. Navigate to your project directory
3. Run: `vercel login`
4. Deploy by running: `vercel`
5. Follow the prompts to complete the deployment

## Testing Your Deployment

After deployment, Vercel will provide you with a URL. Visit this URL to see your visualization.

## Custom Domain

If you want to use a custom domain:
1. Go to your project in the Vercel dashboard
2. Navigate to "Settings" > "Domains"
3. Add your domain and follow the DNS configuration instructions

## Notes

- The visualization loads Plotly.js from a CDN, so internet access is required
- Vercel provides generous free tier limits for personal projects 